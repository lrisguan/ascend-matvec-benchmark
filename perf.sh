#!/bin/bash
echo "running on CPU..."
./out/bin/matvec_cpu
echo "running on NPU"
./out/bin/matvec_ascend
