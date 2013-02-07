PYTHON := python
WAF := ./waf
OPT += 

all:
	$(PYTHON) $(WAF) $(OPT) build
both: release debug
release:
	$(PYTHON) $(WAF) $(OPT) build_release
debug:
	$(PYTHON) $(WAF) $(OPT) build_debug

install:
	$(PYTHON) $(WAF) $(OPT) install
install-debug:
	$(PYTHON) $(WAF) $(OPT) install_debug
install-release:
	$(PYTHON) $(WAF) $(OPT) install_release

uninstall: uninstall-debug uninstall-release
	$(PYTHON) $(WAF) $(OPT) uninstall
uninstall-debug:
	$(PYTHON) $(WAF) $(OPT) uninstall_debug
uninstall-release:
	$(PYTHON) $(WAF) $(OPT) uninstall_release

clean:
	$(PYTHON) $(WAF) $(OPT) clean clean_debug clean_release

distclean:
	$(PYTHON) $(WAF) $(OPT) distclean
	rm -rf build/
	rm -f .lock*
	rm -rf .waf-*
	rm -rf waf-*
