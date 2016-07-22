# pullword

[![CRAN Status Badge](http://www.r-pkg.org/badges/version/pullword)](http://cran.r-project.org/web/packages/pullword)
[![CRAN Downloads](http://cranlogs.r-pkg.org/badges/pullword)](http://cran.rstudio.com/web/packages/pullword/index.html)

An R package for [pullword.com] (http://pullword.com). 

Another package of mine for NLP online service interface is [rLTP](https://github.com/hetong007/rLTP).

# Installation:

To install the version on CRAN, run

```R
install.packages('pullword')
```

To install the (possible) up-to-date version on github, please run

```R
devtools::install_github('hetong007/pullword')
```

Because the `cpp` files, installation from github on Windows requires [Rtools](http://cran.r-project.org/bin/windows/Rtools/).

# Example:

```R
require(pullword)
pullword('清华是个好学校。')
pullword('李彦宏是马云最大威胁嘛？',showProb = TRUE)
```
