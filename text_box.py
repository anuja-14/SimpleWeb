from Tkinter import *

def writecontent(msg ,log ):
    numlines = log.index('end - 1 line').split(' . ')[0]
    log['state']='normal'
    if numlines == 20:
        log.delete(1.0 , 20.0 )
    log.insert('end' , msg)
    log['state']='disabled'

root = Tk()
w = Text ( root , bg = "yellow" , wrap = WORD  );
w.grid()
f = open('text_box.py' , 'r' )
for line in f :
    writecontent(line , w );
root.mainloop()

# Comments on the code of Tkinter : This is a simple code for just showing the file on a window . Read up more on Tkinter and understand the obove code . There are some nice references online . The main thing that we would need to do now , is to look for how to format the output based on some tag . 

# The basic funda being , if we give some style with the markem language . That style sheet will be processed by the parser ( say Beautiful Soup / XML parser in python ) . Using the style sheet given , we would have to set up the property of the display and then display the same to the user. For that you might have to read up also on how to set up the config of the text that is being displayed . For more details , refer http://www.tkdocs.com/tutorial/text.html  . This gives some ideas on how to use the TEXT widget.
