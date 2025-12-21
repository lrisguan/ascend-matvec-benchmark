#!/bin/bash
echo "[C] running on CPU..."
./out/bin/matvec_cpu

echo "[C] running on NPU..."
./out/bin/matvec_ascend

echo "[Py] running on CPU..."
python mindspore/matvec_cpu.py

echo "[Py] runing on NPU..."
python mindspore/matvec_ascend.py
