PYTHON := python
WAF := ./waf
OPT += 

all:
	$(PYTHON) $(WAF) $(OPT) build

both:
	$(PYTHON) $(WAF) $(OPT) build_debug build_release

install:
	$(PYTHON) $(WAF) $(OPT) install

install-debug:
	$(PYTHON) $(WAF) $(OPT) install_debug

install-release:
	$(PYTHON) $(WAF) $(OPT) install_release

uninstall:
	$(PYTHON) $(WAF) $(OPT) uninstall uninstall_debug uninstall_release

clean:
	$(PYTHON) $(WAF) $(OPT) clean clean_debug clean_release

distclean:
	$(PYTHON) $(WAF) $(OPT) distclean
	rm -rf build/
	rm -f .lock*
	rm -rf .waf-*
	rm -rf waf-*
