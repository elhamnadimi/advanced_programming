
'''
Exam requests: 
1. Write a class PostcardList that satisfies the tests (defined using unittest). 
SPECIFICATIONS: 
Class PostcardList reads/writes Postcard messages from/to a properly formatted file: each record (i.e., file's line) is a Postcard. 
The Postcard format is "date:$(DATE); from:$(SENDER); to:$(RECEIVER);" (e.g., "date:2009-12-24; from:Daisy; to:Donald;"). For the sake of simplicity, the message is not considered.
Class PostcardList must have at least these attributes:
 - _file: file name, eventually with the full path.
 - _postcards: list of postcards read from _file.
 - _date: is a dict where the key is the string date, and the value is a list of indices. Each index refers to the corresponding record.
 - _from: is a dict where the key is the string sender, and the value is a list of indices. Each index refers to the corresponding record.
 - _to:   is a dict where the key is the string receiver, and the value is a list of indices. Each index refers to the corresponding record.
Class PostcardList must manage the I/O file through the following member functions. Note that you are free to choose the appropriate arguments, but the function names must be as follows:  
 - writeFile(self,...): write self.{_date,_from,_to} to self._file  
 - readFile(self,...): from self._file read self.{_date,_from,_to}    
 - parsePostcards(self,...): parse self._postcards, set self.{_date,_from,_to} 
 - updateFile(self,...): as write but appending to self._file 
 - updateLists(self,...): as read but appending to self._postcards 
 - getNumberOfPostcards(self): returns length of self._postcards
Class PostcardList must manage the sorting of dates/senders/receivers. Note that the names and arguments of the functions are fixed as follows: 
 - getPostcardsByDateRange(self,date_range): returns the postcards within a date_range
 - getPostcardsBySender(self, sender): returns the postcards from a sender
 - getPostcardsByReceiver(self, receiver): returns the postcards to a receiver
'''

import unittest
import datetime  # use this module to deal with dates:  https://docs.python.org/3/library/datetime.html
import os
import re

class PostcardList: 

    def __init__(self):
        #file name, eventually with the full path
        self._file = None

        #list of postcards read from _file
        self._postcards = []

        #is a dict where the key is the string date, and the value is a list of indices. Each index refers to the corresponding record
        self._date = {}

        #is a dict where the key is the string sender, and the value is a list of indices. Each index refers to the corresponding record
        self._from = {}

        #is a dict where the key is the string receiver, and the value is a list of indices. Each index refers to the corresponding record
        self._to = {}
        

    #write self.{_date,_from,_to} to self._file
    def writeFile(self,file_name):
        with open(file_name,'w') as f:
            for lines in self._postcards:
                f.write(lines + "\n")

    #from self._file read self.{_date,_from,_to}
    def readFile(self, file_name):
        self.updateLists(file_name)
        self.parsePostcards()

    # parse self._postcards, set self.{_date,_from,_to}
    def parsePostcards(self):
        for i,post in enumerate(self._postcards):
            values = post.strip(" ")
            values = re.split(";|:",values)[1::2] 
            try:
                values[0] = datetime.datetime.strptime(values[0],"%Y-%m-%d").date()
            except ValueError:
                print("Date is not in a valid format, line " + i + " will be skipped")
                next
            self.updateDicts(values,i)
            


    def updateDicts(self, keys, value):
        for i,attr in enumerate(["self._date" ,"self._from", "self._to"]):
            if keys[i] not in eval(attr):
                eval(attr)[keys[i]] = [value]
            else:
                eval(attr)[keys[i]].append(value)


    # as write but appending to self._file 
    def updateFile(self, file_name):
        try:
            with open(filename, "a") as f:
                        for line in self._postcards:
                            f.write(line + "\n")
        except IOError:
            print("Could not open the file ", f)

    # as read but appending to self._postcards 
    def updateLists(self, file_name):
        try:
            with open(file_name,'r') as f: 
                self._file = os.path.relpath(file_name)
                for lines in f:
                    self._postcards.append(lines)
        except IOError:
            print("Could not open the file ", f)



    # returns length of self._postcards
    def getNumberOfPostcards(self):
        return len(self._postcards)

    # returns the postcards within a date_range
    def getPostcardsByDateRange(self,date_range):
        old, recent = date_range
        in_the_interval = lambda d: d >=old.date() and d <=recent.date()
        filtered_dates = list(filter(in_the_interval,self._date))
        
        indexes = []
        for d in filtered_dates:
            indexes = indexes + self._date[d]
        
        return [self._postcards[i] for i in indexes]

    # returns the postcards from a sender
    def getPostcardsBySender(self,sender):
        return [self._postcards[i] for i in self._from.get(sender, [])]

    # returns the postcards to a receiver
    def getPostcardsByReceiver(self,receiver):
        return [self._postcards[i] for i in self._to.get(receiver, [])]

    
    ########################


########################
# TO COMMENT 
#from exam_solution import PostcardList # overrides the class define above
########################


class Test(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self._files = ['./exam_postcard_list{}.txt'.format(i) \
                           for i in range(10)]
        self._PstLst = [PostcardList() for f in self._files]
        [p.readFile(f) for f,p in zip(self._files,self._PstLst)]

    def test_missing_attributes(self): 
        attributes_to_define = ['_file','_postcards','_date','_from','_to',\
                                'writeFile','readFile','parsePostcards',\
                                'updateFile','updateLists',\
                                'getNumberOfPostcards',\
                                'getPostcardsByDateRange',\
                                'getPostcardsBySender',\
                                'getPostcardsByReceiver']
        for attr in attributes_to_define:
            if attr not in dir(self._PstLst[0]): 
                raise Exception(attr+' is missing')

    def test_check_getPostcardByDateRange(self): 
        dr_test = []
        for i in [0,1,4,6]: 
            dr_test.append(\
                self._PstLst[i].getPostcardsByDateRange(date_range=\
                   (datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),\
                    datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
        self.assertListEqual(sorted(dr_test[0]),sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n', 'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n'])) 
        self.assertEqual(len(dr_test[1]),1)
        self.assertListEqual(sorted(dr_test[2]),sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n', 'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
        self.assertEqual(len(dr_test[3]),7)

    def test_check_getPostcardBySender(self): 
        s_test = []
        for i in [2,3,5,7]:
            for sender in ['Daisy','Bashful','Peter']:
                s_test.append(\
                    self._PstLst[i].getPostcardsBySender(sender=sender))
        self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n',s_test[0])
        self.assertListEqual(s_test[1],[])
        self.assertEqual(len(s_test[2]),1)
        self.assertEqual(len(s_test[5]),0)
        self.assertGreater(len(s_test[8]),len(s_test[9]))

    def test_check_getPostcardByReceiver(self): 
        r_test = []
        for i in [0,3,8,9]:
            for receiver in ['Peter','Hook','Alice','SnowWhite']:
                r_test.append(\
                  self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
        self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n',r_test[0])
        self.assertListEqual(r_test[1],['date:2016-10-23; from:Sneezy; to:Hook;\n'])
        self.assertEqual(len(r_test[2]),2)
        self.assertEqual(len(r_test[6]),3)

    def test_check_sent_received_when(self): 
        srw_test = []
        for ii in range(10):
            for jj in ["Mickey","Minnie","Goofy","Pluto","Donald","Daisy","$crooge","Huey","Dewey","Louie","Peter","Hook","Alice","SnowWhite","Doc","Sleepy","Sneezy","Bashful","Dopey","Happy","Grumpy"]:
                try:
                    srw_test.append(self._PstLst[ii]._from[jj])
                    srw_test.append(self._PstLst[ii]._to[jj])
                    srw_test.append(self._PstLst[ii]._date[jj])
                except: pass
        self.assertListEqual(srw_test[0],[1])
        self.assertListEqual(srw_test[130],[14,25])
        self.assertListEqual(srw_test[138],[10])
        self.assertListEqual(srw_test[140],[15])
        self.assertListEqual(srw_test[192],[13,26])
        self.assertListEqual(srw_test[203],[6, 9, 11, 12, 24, 31, 42])

if __name__ == '__main__':

    unittest.main()

