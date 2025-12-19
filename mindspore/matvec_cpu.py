import mindspore as ms
import mindspore.ops as ops
import numpy as np
import time

ms.set_context(device_target="CPU")

A = ms.Tensor(np.ones((2048, 2048), np.float32))
B = ms.Tensor(np.ones((2048, 1), np.float32))

start = time.time()
C = ops.MatMul()(A, B)
end = time.time()

print("MindSpore CPU Time:", (end - start) * 1000, "ms")
