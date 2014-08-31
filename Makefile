
NAME=Polybox
VERSION=0.0.1
 
DIRS=Scripts
 
 

install:
	for dir in $(DIRS); do  cd $$dir && $(MAKE) install; done


reinstall:
	for dir in $(DIRS); do  cd $$dir && $(MAKE) reinstall; done
	
.PHONY: install reinstall