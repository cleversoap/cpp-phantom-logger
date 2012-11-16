Phantom Logger
==============

A macro based logging class that is completely removed from compilation when not in use and supports logging to both stdout and a file.

To use simply define either the __\_LOG_PRINT\___ macro (to log to stdout) and/or the __\_LOG_FILE\___ macro with a filename to log to.

I have defined several log types already and these can be removed and added to at will as needed. You may also define whether or not the printed output should go to the std::cout or std::cerr streams via the macro definition.