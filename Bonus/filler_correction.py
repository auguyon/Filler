import os
import subprocess
import re
from threading import Thread

if not os.path.exists("correction"):
	os.makedirs("correction")

class s:
	filler = "resources/./filler_vm -f resources/maps/"
	maps = ["map00", "map01", "map02"]
	p1 = " -p1 ./auguyon.filler"
	p2 = " -p2 resources/players/"
	player = ["abanlin", "carli", "champely", "grati", "hcao", "superjeannot"]
	ext = ".filler"
	args = " -q > correction/"

def launch(p, n, retry):
	if n == 3:
		n = 0;
	while n < 3:
		player2 = orig_string = s.p2 + s.player[p]
		name = orig_string = "auguyon_vs_" + s.player[p] + "_" + s.maps[n]
		if retry != 0:
			name = orig_string = name + "_" + str(retry)
		subprocess.run(s.filler + s.maps[n] + s.p1 + player2 + s.ext + s.args + orig_string, shell=True, stdout=subprocess.PIPE)
		n += 1
		if retry != 0:
			break

def retry(p, n, retry):
	launch(p, n, retry)
	name = orig_string = "correction/auguyon_vs_" + s.player[p] + "_" + s.maps[n] + "_" + str(retry)
	file = open(name, "r")
	content = file.readlines()[-2:]
	content = [int(sc.split('fin: ')[1]) for sc in content]
	if content[0] < content[1]:
		print("Winner " + s.player[p] + " vs auguyon on map0" + str(n) + " : " + str(content[0]) + " vs " + str(content[1]))
		return 0
	else:
		print("Winner auguyon vs " + s.player[p] + " on map0" + str(n) + " : " + str(content[0]) + " vs " + str(content[1]))
		return 1
	return 1

class launcher(Thread):

	def __init__(self, player, maps):
		Thread.__init__(self)
		self.player = player
		self.map = maps

	def run(self):
		launch(self.player, self.map, 0)

thread_0 = launcher(0, 3)
thread_1 = launcher(1, 3)
thread_2 = launcher(2, 3)
thread_3 = launcher(3, 3)
thread_4 = launcher(4, 3)
thread_5 = launcher(5, 3)

thread_0.start()
thread_1.start()
thread_2.start()
thread_3.start()
thread_4.start()
thread_5.start()

thread_0.join()
thread_1.join()
thread_2.join()
thread_3.join()
thread_4.join()
thread_5.join()

p = 0
n = 0
a = 0
while a < 17:
	if p == 6:
		p = 0
		n += 1
	name = orig_string = "correction/auguyon_vs_" + s.player[p] + "_" + s.maps[n]
	file = open(name, "r")
	content = file.readlines()[-2:]
	content = [int(sc.split('fin: ')[1]) for sc in content]
	if content[0] < content[1]:
		print("Winner " + s.player[p] + " vs auguyon on map0" + str(n) + " : " + str(content[0]) + " vs " + str(content[1]))
		ret = retry(p, n, 2)
		if ret != 1:
			retry(p, n, 3)
	else:
		print("Winner auguyon vs " + s.player[p] + " on map0" + str(n) + " : " + str(content[0]) + " vs " + str(content[1]))
	p += 1
	a += 1
	file.close()