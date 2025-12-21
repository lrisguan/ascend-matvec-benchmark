# ascend-matvec-benchmark

***Reference**:[AscendC Example](https://gitee.com/ascend/samples/tree/8.0.RC3/operator/HelloWorldSample)*
> All the [run.sh](./run.sh) code is based on it.
## Directory structure
```bash
├── ascendc               # source code of AscendC
│   ├── CMakeLists.txt
│   ├── main_ascend.cpp
│   └── matvec_kernel.cpp
├── CMakeLists.txt
├── cpu                   # source code of C(run on CPU)
│   ├── CMakeLists.txt
│   └── main_cpu.cpp
├── env
├── mindspore             # source code of python using mindspore
│   ├── ascend.ipynb
│   ├── cpu.ipynb
│   ├── matvec_ascend.py
│   ├── matvec_cpu.py
│   └── offload
├── perf.sh               # perf shell script
├── README.md
└── run.sh                # build and perf shell script
```
## Env
> [!Tip]
> For more detail of hardware and CANN, you can go to [env](./env.md)
- **CPU**: HUAWEI Kunpeng 920 5220
- **NPU**: Atlas 300I Duo
- **CANN**: 8.2.RC2
- **Python**: 3.9.25
- **MindSpore**: 2.7.0

## Quick start
> [!Note]
> I only runs on my Ascend310P3 with CANN version 8.2.RC2, not tested on others. Other types of chip or CANN version may not work for CANN's compatibility.
```bash
git clone https://github.com/lrisguan/ascend-matvec-benchmark.git
cd ascend-matvec-benchmark
pip install mindspore -i https://repo.mindspore.cn/pypi/simple --trusted-host repo.mindspore.cn --extra-index-url https://repo.huaweicloud.com/repository/pypi/simple
# Attention: be sure you've run:
# source /usr/local/Ascend/ascend-toolkit/set_env.sh
# before execute following commands!
./run.sh
# After build, you'll see the benchmark
# if you just want to re-benchmark it, run:
./perf.sh
```
