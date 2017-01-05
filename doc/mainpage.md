ETK library                                 {#mainpage}
===========

What is ETK, and how can I use it?          {#etk_mainpage_what}
==================================

ETK, or Ewol Tool kit is a simple abstraction layer for some elements like mutex, std missing element(in android or MacOS) and ...

We can simply say: Just a tool-box **(I use it to add many test prototyping ... and bad things ...)**


ETK is composed of some part:
  - Log system interface
  - File access abstraction (for android, data are stored in a .apk (== zip file))
  - Mutex / semaphore abstraction (can not use pthread on windows)
  - Regular expression
  - Generic color interface
  - Std adding missing element on some platform.



What languages are supported?               {#etk_mainpage_langue}
=============================

ETK is written in C++.


Are there any licensing restrictions?       {#etk_mainpage_dependency}
=====================================

ETK is **FREE software** and _all sub-library are FREE and staticly linkable !!!_


License (MPL v2.0)                          {#etk_mainpage_licence}
==================

Copyright etk Edouard DUPIN

Licensed under the Mozilla Public License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

<https://www.mozilla.org/MPL/2.0>

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Other pages                              {#etk_mainpage_sub_page}
===========

  - @ref etk_build
  - [**ewol coding style**](http://atria-soft.github.io/ewol/ewol_coding_style.html)



