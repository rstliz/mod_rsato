
MAKE = gmake --no-print-directory


default : main_dir

main_dir :
	$(MAKE) -C main
clean:
	$(MAKE) -C main clean
install:
	$(MAKE) -C main install
reload:
	$(MAKE) -C main reload
start:
	$(MAKE) -C main start
restart:
	$(MAKE) -C main restart
stop:
	$(MAKE) -C main stop