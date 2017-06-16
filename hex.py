import random
import plotly.plotly as py
import plotly
import plotly.graph_objs as go
import numpy as np
import copy
import sys
import time

b = "B" #plays horizontal
r = "R" #plays vertical

def create_grid(size):
	return np.random.uniform(size=(size,size))

def prob_to_player(prob, p):
	if (prob >= p and prob <= 1):
		return b
	elif (prob < p and prob >= 0):
		return r
	else:
		return False


def print_grid(grid):
	for row in range(len(grid)):
		print("  "*row),
		for item in grid[row]:
			print("%s " % prob_to_player(item, 0.5)),
		print


def floodfill_rec(matrix, x, y, p):
    #"hidden" stop clause - not reinvoking for "c" or "b", only for "a".
    if prob_to_player(matrix[x][y], p) == r:  
        matrix[x][y] = -1
        #recursively invoke flood fill on all surrounding cells:
        if x > 0:
            floodfill_rec(matrix,x-1,y, p)
        if x > 0 and y < len(matrix) -1:
        	floodfill_rec(matrix,x-1,y+1, p)
        if x < len(matrix) - 1:
            floodfill_rec(matrix,x+1,y, p)
        if y > 0:
            floodfill_rec(matrix,x,y-1, p)
        if y < len(matrix) - 1:
            floodfill_rec(matrix,x,y+1, p)
        if y > 0 and x < len(matrix) -1:
        	floodfill_rec(matrix,x+1,y-1, p)

def floodfill(matrix, x, y, p):
    #"hidden" stop clause - not reinvoking for "c" or "b", only for "a".
    stack = [[x,y]]
    board_size = len(matrix)
    while True:
    	if len(stack) == 0:
    		del stack
    		return
    	[x,y] = stack.pop()
    	if prob_to_player(matrix[x][y], p) == r:
	        matrix[x][y] = -1
	        if x == board_size - 1:
	        	del stack
	        	return
	        #recursively invoke flood fill on all surrounding cells:
	        if x > 0:
	        	stack.append([x-1,y])
	        if x > 0 and y < len(matrix) -1:
	        	stack.append([x-1,y+1])
	        if x < len(matrix) - 1:
	        	stack.append([x+1,y])
	        if y > 0:
	        	stack.append([x,y-1])
	        if y < len(matrix) - 1:
	        	stack.append([x,y+1])
	        if y > 0 and x < len(matrix) -1:
	        	stack.append([x+1,y-1])


def determine_winner(grid, p=0.5):
	for i in range(len(grid)):
		c = copy.deepcopy(grid)
		floodfill(c,0,i,p)
		if any([item == -1 for item in c[-1]]):
			return r, c
		del c
	return b, None

def create_trace(size,delta,freq):

	wins = []
	ps = []
	for p in np.arange(0.2, 0.8, delta):
		count = 0
		start = time.time()
		for x in range(freq):
			grid = create_grid(size)
			if determine_winner(grid, p)[0] == r:
				count += 1
			del grid

		wins += [float(count)/freq]
		ps += [p]

		end = time.time()
		print("Boards size: %d, time per board: %f" % (size, (end - start)/freq ))

	trace0 = go.Scatter(
	    x = ps,
	    y = wins,
	    mode = 'lines',
	    name = 'hex %d*%d' %(size,size)
	)

	return trace0


def plot_hex_critical(sizes,delta,freq):

	
	data = [create_trace(size, delta, freq) for size in sizes]

	layout = go.Layout(
	    title="Critical probability p",
	    xaxis=dict(
	        title='probability of making move',
	        titlefont=dict(
	            family='Courier New, monospace',
	            size=18,
	            color='#7f7f7f'
	        )
	    ),
	    yaxis=dict(
	        title='probability of winning',
	        titlefont=dict(
	            family='Courier New, monospace',
	            size=18,
	            color='#7f7f7f'
	        )
	    )
	)

	
	fig = go.Figure(data=data, layout=layout)
	plot_url = py.plot(fig, filename="hex %s" % ",".join([ "%d*%d" % (size,size) for size in sizes]))


def plot_critical():
	sizes = [1000,500,200,100,50,20,10,5,3,2][::-1]
	plot_hex_critical(sizes, 0.02, 1000)

def pivotal_sites(grid, p=0.5):
	size = grid.shape[0]
	nr = 0
	winner = determine_winner(grid, p)[0]
	for i in range(size):
		for j in range(size):
			grid[i][j] = 1.0 - grid[i][j]
			if determine_winner(grid, p)[0] != winner:
				nr += 1
			grid[i][j] = 1.0 - grid[i][j]
	del grid
	return nr

def pivotal_sites_new(grid, p=0.5):
	size = grid.shape[0]
	nr = 0
	winner, c = determine_winner(grid, p)
	if winner == r:
		for i in range(size):
			for j in range(size):
				if c[i][j] == -1:
					grid[i][j] = 1.0 - grid[i][j]
					if determine_winner(grid, p)[0] != winner:
						nr += 1
					grid[i][j] = 1.0 - grid[i][j]
	else:
		for i in range(size):
			for j in range(size):
				grid[i][j] = 1.0 - grid[i][j]
				if determine_winner(grid, p)[0] != winner:
					nr += 1
				grid[i][j] = 1.0 - grid[i][j]
	del grid
	return nr

def average_pivotal_sites(size, runs, p=0.5, info=True):
	sites = []
	start = time.time()
	for x in range(1,runs+1):
		grid = create_grid(size)
		sites += [pivotal_sites_new(grid, p)]
		if info and x % 100 == 0:
			end = time.time()
			print("step: %d, #pivotal sites:%f, seconds/site:%f" %(x, float(sum(sites))/x, (end-start)/100))
			start = time.time()
	return float(sum(sites))/runs, sites


def exact_pivotal_sites(size, info=True):
	import itertools
	x = [0,1]
	boards = [p for p in itertools.product(x, repeat=(size*size))]
	total = len(boards)
	board_result = dict()
	start = time.time()
	for i, b in enumerate(boards, 1):
		if info and i % 10000 == 0:
			end = time.time()
			print("step: %d-%d, seconds/site:%f" %(i,total, (end-start)/10000))
			start = time.time()

		s = "".join([str(a) for a in b])
		a = np.asarray(b)
		a = a.reshape((size,size))
		board_result[s] = determine_winner(a)[0]

	sites = 0
	start = time.time()
	for i, b in enumerate(board_result, 1):
		if info and i % 10000 == 0:
			end = time.time()
			print("step: %d-%d, #pivotal sites:%f, seconds/site:%f" %(i,total, float(sites)/i, (end-start)/10000))
			start = time.time()

		for j in range(size*size):
			if b[j] == '1':
				b_complement = b[:j] + '0' + b[j+1:]
			else:
				b_complement = b[:j] + '1' + b[j+1:]

			if board_result[b] != board_result[b_complement]:
				sites += 1

	print float(sites)/total


def plot_average_pivotal_sites():
	prob = np.arange(0.2, 0.85, 0.05)
	boards = [2,3,5,9,11,15,20]
	results = np.zeros(shape=(len(boards),len(prob)))
	for x in range(len(boards)):
		for y in range(len(prob)):
			results[x][y] = average_pivotal_sites(size=boards[x],runs=2000, p=prob[y])


	trace = go.Heatmap(z=results,
	                   y=["%d*%d" % (b,b) for b in boards],
	                   x=prob)
	data=[trace]
	fig = go.Figure(data=data)
	plot_url = py.plot(fig, filename="average number of pivotal sites")


def fit_data(x,y, plot=False):

	from scipy.optimize import curve_fit
	import pylab

	def func(x, a):
	    return np.power(x,a)

	popt, pcov = curve_fit(func, x, y, [2])
	print("Exponent: %f" % popt)

	if plot:
		print y
		print func(x,*popt)
		pylab.plot(x,y)
		x=pylab.linspace(min(x),max(x)+20)
		pylab.plot(x,func(x,*popt))
		pylab.show()


def make_curve():


	x,y = [],[]
	traces = []
	for i in range(10,20):
		s, sites = average_pivotal_sites(i, 500, info=False)
		y += [s**2]
		x += [i]
		print(i,s)
		fit_data(x,y)
		traces += [go.Box( 	y=sites,  
        					name="%d" % i )
					]


	fig = go.Figure(data=traces)
	plot_url = py.plot(fig, filename="average number of pivotal sites")

	x = np.array(x)
	y = np.array(y)
	fit_data(x,y, plot=True)




if __name__ == '__main__':
	average_pivotal_sites(15,10**5,p=0.5)
	