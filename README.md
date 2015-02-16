# pullword

An R package for [pullword.com] (http://pullword.com). 

Another package of mine for NLP online service interface is [rLTP](https://github.com/hetong007/rLTP).

# Installation:

```R
devtools::install_github('hetong007/pullword')
```

# Example:

```R
require(pullword)
pullword('清华是个好学校。')
pullword('李彦宏是马云最大威胁嘛？',showProb = TRUE)
```
