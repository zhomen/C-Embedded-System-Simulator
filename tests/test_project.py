# tests/test_project.py
import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT / "build"

def run(command, cwd=ROOT):
    result = subprocess.run(
        command,
        cwd=cwd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )

    assert result.returncode == 0, (
        f"Command failed: {' '.join(command)}\n"
        f"STDOUT:\n{result.stdout}\n"
        f"STDERR:\n{result.stderr}"
    )

    return result

def test_project_builds():
    BUILD_DIR.mkdir(exist_ok=True)

    run(["cmake", ".."], cwd=BUILD_DIR)
    run(["cmake", "--build", "."], cwd=BUILD_DIR)

def test_cpp_tests_pass():
    run(["cmake", ".."], cwd=BUILD_DIR)
    run(["cmake", "--build", "."], cwd=BUILD_DIR)

    test_binary = BUILD_DIR / "Debug/sensor_tests"
    result = run([str(test_binary)], cwd=BUILD_DIR)

    assert "All C++ tests passed" in result.stdout

def test_simulator_runs():
    run(["cmake", ".."], cwd=BUILD_DIR)
    run(["cmake", "--build", "."], cwd=BUILD_DIR)

    app_binary = BUILD_DIR / "Debug/sensor_sim"
    result = run([str(app_binary)], cwd=BUILD_DIR)

    assert "Event type=" in result.stdout