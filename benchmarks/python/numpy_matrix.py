import time
import numpy as np

if __name__ == '__main__':
    A = np.random.rand(1024, 1024)
    B = np.random.rand(1024, 1024)
    
    t_ref = time.time()

    C = A@B

    print('Elapsed time = {:} ms'.format((time.time() - t_ref) * 1000))
