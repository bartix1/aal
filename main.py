import matplotlib.pyplot as plt

def createDiagram(times):
	#print(times)[:10]
	plt.plot([int(i) for i in range(len(times))], times)
	plt.ylabel('times')
	plt.xlabel('shelf size')
	plt.show()

def easy():
	print("WITAM")