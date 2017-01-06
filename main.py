import matplotlib.pyplot as plt

def createDiagram(times):
	#print(times)[:10]
	plt.plot([i[0] for i in times], [i[1] for i in times])
	plt.ylabel('times')
	plt.xlabel('shelf size')
	plt.show()
