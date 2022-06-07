// Copyright (c) 2011-2022 The Khronos Group, Inc.
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <CL/sycl.hpp>
using namespace sycl; // (optional) avoids need for "sycl::" before SYCL names

int main() {
  constexpr int num_items = 32;
  int data[num_items];  // Allocate data to be worked on

  // Create a default queue to enqueue work to the GPU
  queue myQueue{gpu_selector{}};

  std::cout << "Running on "
            << myQueue.get_device().get_info<sycl::info::device::name>()
            << "\n";

  // By wrapping all the SYCL work in a {} block, we ensure
  // all SYCL tasks must complete before exiting the block,
  // because the destructor of resultBuf will wait
  {
    // Wrap our data variable in a buffer
    buffer<int, 1> resultBuf { data, range<1> { num_items } };

    // Create a command group to issue commands to the queue
    myQueue.submit([&](handler& cgh) {
      // Request write access to the buffer without initialization
      accessor writeResult { resultBuf, cgh, write_only, no_init };

      // Enqueue a parallel_for task with num_items work-items
      cgh.parallel_for(num_items, [=](id<1> idx) {
        // Initialize each buffer element with its own rank number starting at 0
        writeResult[idx] = idx;
      });  // End of the kernel function
    });    // End of our commands for this queue
  }        // End of scope, so we wait for work producing resultBuf to complete

  // Print result
  for (int i = 0; i < num_items; i++)
    std::cout << "data[" << i << "] = " << data[i] << std::endl;

  return 0;
}
