target:
	cd lib/shm; make target
	cd lib/usb; make target
	cd lib/sem; make target
	cd gamepad; make target
	cd webserver/cgi-bin; make target
	@echo "Juw pils"

host:
	cd lib/shm; make host
	@echo "Juw pils"

findpi:
	sudo arp-scan --interface=eth1 --localnet

upload:
	scp gamepad/gamepad.out root@192.168.0.49:/usr/bin
	scp webserver/cgi-bin/mq.out root@192.168.0.49:/var/www/cgi-bin
	scp webserver/cgi-bin/shm.out root@192.168.0.49:/var/www/cgi-bin

uploadweb:
	scp webserver/gamepad.html root@192.168.0.49:/var/www