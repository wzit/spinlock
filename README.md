spinlock
========

## description

A user-space spinlock implementation for C++11 and later. This implementation
is part of the [dsa (data structures and algorithms) library]
(https://github.com/daltonwoodard/dsa.git).

Depending on the application, spinlocks are a more efficient alternative to
traditional synchronization methods such as mutexes and semaphores. In
particular, if a lock only needs to be held by a thread for a short time span,
then the spinlock approach (also known as busy-waiting) will be more efficient.
For example, if a thread only needs to make minor changes to a global structure
or make an alteration to the program state in a synchronized manner, then
spinlocks will typically be a good choice.

## dependencies

Compiler support for C++11 or later.

## info

### author

Dalton Woodard

### contact

daltonmwoodard@gmail.com

### official repository

#### spinlock

https://github.com/daltonwoodard/spinlock.git

#### dsa

https://github.com/daltonwoodard/dsa.git

### License

All of the following information is reproduced in [COPYRIGHT](COPYRIGHT.txt).

spinlock is distributed under a dual MIT License and Apache-2.0 License as part
of the dsa library. You, the licensee, may choose either at your option. The MIT
License is GPL compatible, while the Apache-2.0 License is not, so please take
this into consideration.

Also note that by choosing *either* the MIT license *or* Apache-2.0 license
you are required to provide attribution in the form of copyright reproduction
(the details of which are subject to the license you choose).

The terms of each can be found in the files [LICENSE-MIT](LICENSE-MIT) and
[LICENSE-APACHE-2.0](LICENSE-APACHE-2.0), respectively. The notices of each are
reproduced here for convenience:

---

MIT License (MIT)

Copyright (c) 2016 Dalton M. Woodard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

Copyright 2016 Dalton M. Woodard

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
