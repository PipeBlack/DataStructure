import os

for root,dirs,files in os.walk('./ch01',topdown=False):
    '''
    for name in files:
        FilePath=os.path.join(root,name)
        if(not FilePath.endswith(".c")):
            FileToRemove=os.path.join(root,name)
            os.remove(FileToRemove)
    '''
    for name in dirs:
        OperateDir=os.path.join(root,name)
        print(OperateDir)
        if not os.listdir(OperateDir):
            os.rmdir(OperateDir)
    
