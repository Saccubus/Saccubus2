# Saccubus
# Copyright (C) 2013 psi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
