import time
import warnings
import os
warnings.filterwarnings("ignore", category=UserWarning, module="numpy")
warnings.filterwarnings("ignore", message=".*device_target.*will be deprecated.*")
os.environ['GLOG_minloglevel'] = '2'
import mindspore as ms
import mindspore.ops as ops
import numpy as np

ms.set_device(device_target="Ascend")

A = ms.Tensor(np.ones((2048, 2048), np.float32))
B = ms.Tensor(np.ones((2048, 1), np.float32))
              
C = ops.MatMul()(A, B)
sum = 0.0
for _ in range(10000):
    start = time.time()
    C = ops.MatMul()(A, B)
    end = time.time()
    sum += (end - start) * 1000
print("MindSpore Ascend MatVec Average Time:", sum / 10000, "ms")