#!/usr/bin/env python3
"""
Script de test de performance (perft) pour le moteur d'échecs.
Compare les résultats du programme avec les valeurs attendues du fichier EPD.
"""

import subprocess
import re
import time
import argparse
from pathlib import Path
from dataclasses import dataclass
from typing import Optional


@dataclass
class PerftResult:
    """Résultat d'un test perft."""
    fen: str
    depth: int
    expected_nodes: int
    actual_nodes: Optional[int] = None
    time_ms: Optional[float] = None
    passed: bool = False
    error: Optional[str] = None


def parse_epd_line(line: str) -> dict:
    """
    Parse une ligne du fichier EPD.
    Format: FEN ;D1 nodes ;D2 nodes ;D3 nodes ...
    Retourne: {'fen': str, 'depths': {1: nodes, 2: nodes, ...}}
    """
    line = line.strip()
    if not line:
        return None
    
    # Séparer la FEN des résultats attendus
    parts = line.split(';')
    fen = parts[0].strip()
    
    depths = {}
    for part in parts[1:]:
        part = part.strip()
        match = re.match(r'D(\d+)\s+(\d+)', part)
        if match:
            depth = int(match.group(1))
            nodes = int(match.group(2))
            depths[depth] = nodes
    
    return {'fen': fen, 'depths': depths}


def run_perft(prog_path: str, fen: str, depth: int, timeout: int = 300) -> tuple[Optional[int], Optional[float], Optional[str]]:
    """
    Exécute le programme avec une position et une profondeur donnée.
    Retourne: (nodes, time_ms, error)
    """
    try:
        # Lancer le programme
        process = subprocess.Popen(
            [prog_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Envoyer les commandes
        commands = f"position fen {fen}\ngo perft {depth}\nquit\n"
        stdout, stderr = process.communicate(input=commands, timeout=timeout)
        
        # Parser la sortie
        nodes = None
        time_ms = None
        
        for line in stdout.split('\n'):
            line = line.strip()
            # Chercher "Time X" ou "time X"
            time_match = re.search(r'[Tt]ime\s+(\d+(?:\.\d+)?)', line)
            if time_match:
                time_ms = float(time_match.group(1))
            
            # Chercher "nodes X" ou "Nodes X"
            nodes_match = re.search(r'[Nn]odes\s+(\d+)', line)
            if nodes_match:
                nodes = int(nodes_match.group(1))
        
        return nodes, time_ms, None
        
    except subprocess.TimeoutExpired:
        process.kill()
        return None, None, f"Timeout après {timeout}s"
    except Exception as e:
        return None, None, str(e)


def load_epd_file(epd_path: str) -> list[dict]:
    """Charge et parse le fichier EPD."""
    positions = []
    with open(epd_path, 'r') as f:
        for line in f:
            parsed = parse_epd_line(line)
            if parsed:
                positions.append(parsed)
    return positions


def run_tests(prog_path: str, epd_path: str, depth: int, max_positions: Optional[int] = None, verbose: bool = True) -> list[PerftResult]:
    """
    Exécute les tests perft pour toutes les positions.
    """
    positions = load_epd_file(epd_path)
    
    if max_positions:
        positions = positions[:max_positions]
    
    results = []
    total = len(positions)
    
    print(f"\n{'='*60}")
    print(f"Test Perft - Profondeur {depth}")
    print(f"Fichier EPD: {epd_path}")
    print(f"Nombre de positions: {total}")
    print(f"{'='*60}\n")
    
    for i, pos in enumerate(positions, 1):
        fen = pos['fen']
        expected = pos['depths'].get(depth)
        
        if expected is None:
            if verbose:
                print(f"[{i}/{total}] Position sans D{depth}: {fen[:50]}...")
            continue
        
        result = PerftResult(fen=fen, depth=depth, expected_nodes=expected)
        
        if verbose:
            print(f"[{i}/{total}] Testing: {fen[:50]}...", end=" ", flush=True)
        
        nodes, time_ms, error = run_perft(prog_path, fen, depth)
        
        result.actual_nodes = nodes
        result.time_ms = time_ms
        result.error = error
        result.passed = (nodes == expected)
        
        if verbose:
            if error:
                print(f"❌ ERREUR: {error}")
            elif result.passed:
                nps = int(nodes / (time_ms / 1000)) if time_ms and time_ms > 0 else 0
                print(f"✅ OK ({nodes} nodes, {time_ms:.0f}ms, {nps:,} nps)")
            else:
                print(f"❌ FAIL (attendu: {expected}, obtenu: {nodes})")
        
        results.append(result)
    
    return results


def run_all_depths_tests(prog_path: str, epd_path: str, max_depth: int = 6, max_positions: Optional[int] = None, verbose: bool = True) -> dict[int, list[PerftResult]]:
    """
    Exécute les tests perft pour toutes les profondeurs de 1 à max_depth.
    """
    all_results = {}
    
    for depth in range(1, max_depth + 1):
        results = run_tests(prog_path, epd_path, depth, max_positions, verbose)
        all_results[depth] = results
    
    return all_results


def print_all_depths_summary(all_results: dict[int, list[PerftResult]]):
    """Affiche un résumé global pour tous les tests à toutes les profondeurs."""
    print(f"\n{'='*70}")
    print("RÉSUMÉ GLOBAL - TOUTES PROFONDEURS")
    print(f"{'='*70}")
    print(f"{'Depth':<8} {'Total':<8} {'Réussis':<10} {'Échecs':<8} {'Erreurs':<8} {'%':<8} {'Temps':<12} {'NPS':<15}")
    print(f"{'-'*70}")
    
    grand_total = 0
    grand_passed = 0
    grand_failed = 0
    grand_errors = 0
    grand_nodes = 0
    grand_time = 0
    
    for depth in sorted(all_results.keys()):
        results = all_results[depth]
        total = len(results)
        passed = sum(1 for r in results if r.passed)
        failed = sum(1 for r in results if not r.passed and r.error is None)
        errors = sum(1 for r in results if r.error is not None)
        total_nodes = sum(r.actual_nodes or 0 for r in results)
        total_time = sum(r.time_ms or 0 for r in results)
        pct = 100 * passed / total if total > 0 else 0
        nps = int(total_nodes / (total_time / 1000)) if total_time > 0 else 0
        
        print(f"D{depth:<7} {total:<8} {passed:<10} {failed:<8} {errors:<8} {pct:<7.1f}% {total_time:<11.0f}ms {nps:,}")
        
        grand_total += total
        grand_passed += passed
        grand_failed += failed
        grand_errors += errors
        grand_nodes += total_nodes
        grand_time += total_time
    
    print(f"{'-'*70}")
    grand_pct = 100 * grand_passed / grand_total if grand_total > 0 else 0
    grand_nps = int(grand_nodes / (grand_time / 1000)) if grand_time > 0 else 0
    print(f"{'TOTAL':<8} {grand_total:<8} {grand_passed:<10} {grand_failed:<8} {grand_errors:<8} {grand_pct:<7.1f}% {grand_time:<11.0f}ms {grand_nps:,}")
    print(f"{'='*70}")
    print(f"Total nodes: {grand_nodes:,}")
    print(f"Temps total: {grand_time/1000:.2f}s ({grand_time/60000:.2f}min)")
    print(f"{'='*70}")
    
    # Collecter tous les échecs
    all_failures = []
    for depth, results in all_results.items():
        for r in results:
            if not r.passed and r.error is None:
                all_failures.append(r)
    
    if all_failures:
        print(f"\nÉCHECS DÉTAILLÉS ({len(all_failures)} total):")
        print("-" * 70)
        for r in all_failures[:20]:  # Limiter à 20
            print(f"D{r.depth} | FEN: {r.fen}")
            print(f"     Attendu: {r.expected_nodes}, Obtenu: {r.actual_nodes}, Diff: {r.actual_nodes - r.expected_nodes}")
            print()


def print_summary(results: list[PerftResult]):
    """Affiche un résumé des résultats."""
    total = len(results)
    passed = sum(1 for r in results if r.passed)
    failed = sum(1 for r in results if not r.passed and r.error is None)
    errors = sum(1 for r in results if r.error is not None)
    
    total_nodes = sum(r.actual_nodes or 0 for r in results)
    total_time = sum(r.time_ms or 0 for r in results)
    
    print(f"\n{'='*60}")
    print("RÉSUMÉ DES TESTS")
    print(f"{'='*60}")
    print(f"Total des tests:     {total}")
    print(f"Réussis:             {passed} ({100*passed/total:.1f}%)" if total > 0 else "Réussis: 0")
    print(f"Échecs:              {failed}")
    print(f"Erreurs:             {errors}")
    print(f"{'='*60}")
    print(f"Total nodes:         {total_nodes:,}")
    print(f"Temps total:         {total_time:.0f} ms ({total_time/1000:.2f} s)")
    if total_time > 0:
        avg_nps = int(total_nodes / (total_time / 1000))
        print(f"Vitesse moyenne:     {avg_nps:,} nps")
    print(f"{'='*60}")
    
    # Afficher les échecs
    failed_results = [r for r in results if not r.passed and r.error is None]
    if failed_results:
        print("\nÉCHECS DÉTAILLÉS:")
        print("-" * 60)
        for r in failed_results[:10]:  # Limiter à 10
            print(f"FEN: {r.fen}")
            print(f"  Attendu: {r.expected_nodes}, Obtenu: {r.actual_nodes}")
            print()


def main():
    # Déterminer le répertoire racine du projet (parent de perf/)
    script_dir = Path(__file__).parent.resolve()
    project_root = script_dir.parent
    
    parser = argparse.ArgumentParser(description="Test de performance perft pour moteur d'échecs")
    parser.add_argument('-p', '--prog', default=None, help='Chemin vers le programme (défaut: ./prog depuis la racine)')
    parser.add_argument('-e', '--epd', default=None, help='Fichier EPD (défaut: perf/standard.epd)')
    parser.add_argument('-d', '--depth', type=int, default=4, help='Profondeur de recherche (défaut: 4)')
    parser.add_argument('-a', '--all-depths', action='store_true', help='Tester toutes les profondeurs (D1 à D6)')
    parser.add_argument('--max-depth', type=int, default=6, help='Profondeur max pour --all-depths (défaut: 6)')
    parser.add_argument('-n', '--max-positions', type=int, help='Nombre max de positions à tester')
    parser.add_argument('-q', '--quiet', action='store_true', help='Mode silencieux')
    
    args = parser.parse_args()
    
    # Résoudre les chemins par défaut relatifs au projet
    prog_path = Path(args.prog).resolve() if args.prog else project_root / 'prog'
    epd_path = Path(args.epd).resolve() if args.epd else script_dir / 'standard.epd'
    
    # Vérifier que le programme existe
    if not prog_path.exists():
        print(f"Erreur: Programme '{prog_path}' non trouvé")
        return 1
    
    # Vérifier que le fichier EPD existe
    if not epd_path.exists():
        print(f"Erreur: Fichier EPD '{epd_path}' non trouvé")
        return 1
    
    # Mode toutes profondeurs ou profondeur unique
    if args.all_depths:
        all_results = run_all_depths_tests(
            str(prog_path),
            str(epd_path),
            args.max_depth,
            args.max_positions,
            verbose=not args.quiet
        )
        print_all_depths_summary(all_results)
        # Retourner 0 si tous les tests passent
        all_passed = all(r.passed for results in all_results.values() for r in results)
        return 0 if all_passed else 1
    else:
        # Exécuter les tests pour une seule profondeur
        results = run_tests(
            str(prog_path),
            str(epd_path),
            args.depth,
            args.max_positions,
            verbose=not args.quiet
        )
        
        # Afficher le résumé
        print_summary(results)
        
        # Retourner 0 si tous les tests passent, 1 sinon
        return 0 if all(r.passed for r in results) else 1


if __name__ == '__main__':
    exit(main())
