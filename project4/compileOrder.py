def compileOrder(targets):
    stack = []
    visited = {}
    def defOrder(key):       
        visited[key] = True
        if key in targets:
            for item in targets[key]:
                if item not in visited :
                    defOrder(item)    
        stack.append(key)
           
    for key in targets.keys():
        if key not in visited :
            defOrder(key)
   
    print (stack[0:])
    

def testcompileOrder():
    targets  =  {'target0.go': ['target1.go', 'target2.go','target3.go','target4.go'],'target1.go': ['target5.go', 'target6.go','target4.go'],
              'target2.go': ['target9.go', 'target7.go','target4.go'],'target3.go': ['target6.go', 'target4.go']}
 
    compileOrder(targets)

testcompileOrder()