Build lib & build sample                           {#etk_build}
========================

@tableofcontents

Download:                                          {#etk_build_download}
=========

etk use some tools to manage source and build it:

lutin (build-system):                              {#etk_build_download_lutin}
---------------------

```{.sh}
	pip install lutin --user
	# optionnal dependency of lutin (manage image changing size for application release
	pip install pillow --user
```


dependency:                                        {#etk_build_download_dependency}
-----------

```{.sh}
	mkdir framework
	cd framework
	git clone https://github.com/atria-soft/elog.git
	cd ..
```

sources:                                           {#etk_build_download_sources}
--------

```{.sh}
	cd framework
	git clone https://github.com/atria-soft/etk.git
	cd ..
```

Build:                                             {#etk_build_build}
======


library:                                           {#etk_build_build_library}
--------

```{.sh}
	lutin -mdebug etk
```

test:                                            {#etk_build_build_sample}
-----

```{.sh}
	lutin -mdebug etk-test
```

Or simple:

```{.sh}
	lutin -mdebug etk-*
```

Run sample:                                        {#etk_build_run_sample}
===========

```{.sh}
	lutin -mdebug etk-test?run
```
