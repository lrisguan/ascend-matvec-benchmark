# ascend-matvec-benchmark

***Reference**:[AscendC Example](https://gitee.com/ascend/samples/tree/8.0.RC3/operator/HelloWorldSample)*
> All the [run.sh](./run.sh) code is based on it.
- Directory structure
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
- **env**
    - **cpu**
    ```bash
    Architecture:                    aarch64
    CPU op-mode(s):                  64-bit
    Byte Order:                      Little Endian
    CPU(s):                          64
    On-line CPU(s) list:             0-63
    Thread(s) per core:              1
    Core(s) per socket:              32
    Socket(s):                       2
    NUMA node(s):                    2
    Vendor ID:                       0x48
    Model:                           0
    Stepping:                        0x1
    CPU max MHz:                     2600.0000
    CPU min MHz:                     200.0000
    BogoMIPS:                        200.00
    L1d cache:                       4 MiB
    L1i cache:                       4 MiB
    L2 cache:                        32 MiB
    L3 cache:                        64 MiB
    NUMA node0 CPU(s):               0-31
    NUMA node1 CPU(s):               32-63
    Vulnerability Itlb multihit:     Not affected
    Vulnerability L1tf:              Not affected
    Vulnerability Mds:               Not affected
    Vulnerability Meltdown:          Not affected
    Vulnerability Mmio stale data:   Not affected
    Vulnerability Spec store bypass: Not affected
    Vulnerability Spectre v1:        Mitigation; __user pointer sanitization
    Vulnerability Spectre v2:        Not affected
    Vulnerability Srbds:             Not affected
    Vulnerability Tsx async abort:   Not affected
    Flags:                           fp asimd evtstrm aes pmull sha1 sha2 crc32 atomics fphp asimdhp cpuid asimdrdm jscvt fc
                                    ma dcpop asimddp asimdfhm
    ```
    - **npu**
    ```bash
    +--------------------------------------------------------------------------------------------------------+
    | npu-smi 25.2.0                                   Version: 25.2.0                                       |
    +-------------------------------+-----------------+------------------------------------------------------+
    | NPU     Name                  | Health          | Power(W)     Temp(C)           Hugepages-Usage(page) |
    | Chip    Device                | Bus-Id          | AICore(%)    Memory-Usage(MB)                        |
    +===============================+=================+======================================================+
    | 2       310P3                 | OK              | NA           51                0     / 0             |
    | 0       0                     | 0000:01:00.0    | 0            1529 / 44280                            |
    +-------------------------------+-----------------+------------------------------------------------------+
    | 2       310P3                 | OK              | NA           49                0     / 0             |
    | 1       1                     | 0000:01:00.0    | 0            1411 / 43693                            |
    +===============================+=================+======================================================+
    +-------------------------------+-----------------+------------------------------------------------------+
    | NPU     Chip                  | Process id      | Process name             | Process memory(MB)        |
    +===============================+=================+======================================================+
    | No running processes found in NPU 2                                                                    |
    +===============================+=================+======================================================+
    ```
    - **CANN**
    ```bash
    # version: 1.0
    runtime_running_version=[8.2.0.2.220:8.2.RC2]
    compiler_running_version=[8.2.0.2.220:8.2.RC2]
    hccl_running_version=[8.2.0.2.220:8.2.RC2]
    opp_running_version=[8.2.0.2.220:8.2.RC2]
    toolkit_running_version=[8.2.0.2.220:8.2.RC2]
    aoe_running_version=[8.2.0.2.220:8.2.RC2]
    ncs_running_version=[8.2.0.2.220:8.2.RC2]
    opp_kernel_running_version=[8.2.0.2.220:8.2.RC2]
    opp_kernel_upgrade_version=[8.2.0.2.220:8.2.RC2]
    runtime_upgrade_version=[8.2.0.2.220:8.2.RC2]
    compiler_upgrade_version=[8.2.0.2.220:8.2.RC2]
    hccl_upgrade_version=[8.2.0.2.220:8.2.RC2]
    opp_upgrade_version=[8.2.0.2.220:8.2.RC2]
    toolkit_upgrade_version=[8.2.0.2.220:8.2.RC2]
    aoe_upgrade_version=[8.2.0.2.220:8.2.RC2]
    ncs_upgrade_version=[8.2.0.2.220:8.2.RC2]
    opp_kernel_installed_version=[7.5.T11.0.B081:8.0.RC3.alpha003][8.2.0.2.220:8.2.RC2]
    runtime_installed_version=[8.2.0.2.220:8.2.RC2]
    compiler_installed_version=[8.2.0.2.220:8.2.RC2]
    hccl_installed_version=[8.2.0.2.220:8.2.RC2]
    opp_installed_version=[8.2.0.2.220:8.2.RC2]
    toolkit_installed_version=[8.2.0.2.220:8.2.RC2]
    aoe_installed_version=[8.2.0.2.220:8.2.RC2]
    ncs_installed_version=[8.2.0.2.220:8.2.RC2]
    ```
- Quick start
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
