import subprocess
from tkinter import *
from tkinter import ttk
import os


def client_tube(second_frame):
   Commande="\" ../tube_nomme/Client >> liste.txt; exec bash\""
   subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande}",shell=True)
   f = open("liste.txt")
   lines=f.readlines()
   for line in lines:
      temp_text = line
      Label(second_frame, text=temp_text).pack()
   f.close()

def client_socket(second_frame,nb_client):
   ///////////////
                
   subprocess.Popen(f"gnome-terminal --tab -- bash -c {commande}",shell=True)
   f = open("liste2.txt")
   lines=f.readlines()
   for line in lines:
      temp_text = line
      Label(second_frame, text=temp_text).pack()
   f.close()
   os.remove("liste2.txt")

def sel():
   if v.get()=="Tube":
      Commande1="\" ../tube_nomme/server; exec bash\""
      subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande1}",shell=True)
      gui2 = Toplevel(gui)
      gui2.geometry("650x450")

      frame = Frame(gui2)
      frame.pack(expand=True, fill=BOTH, padx=20, pady=20)
      # Create A Canvas
      my_canvas = Canvas(frame)
      my_canvas.pack(side=LEFT, fill=BOTH, expand=1)

      # Add A Scrollbar To The Canvas
      my_scrollbar = ttk.Scrollbar(frame, orient=VERTICAL, command=my_canvas.yview)
      my_scrollbar.pack(side=RIGHT, fill=Y)

      # Configure The Canvas
      my_canvas.configure(yscrollcommand=my_scrollbar.set)
      my_canvas.bind('<Configure>', lambda e: my_canvas.configure(scrollregion = my_canvas.bbox("all")))

      # Create ANOTHER Frame INSIDE the Canvas
      second_frame = Frame(my_canvas)

      # Add that New frame To a Window In The Canvas
      my_canvas.create_window((0,0), window=second_frame, anchor="nw")
            
      btn = Button(gui2, text ="Lancer un Client",command=lambda:client_tube(second_frame))
      btn.pack()
      gui2.mainloop()
   if v.get()=="Sockets":
      Commande1="\" ../Sockets/server; exec bash\""
      subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande1}",shell=True)
      gui2 = Toplevel(gui)
      gui2.geometry("650x450")
   
      frame = Frame(gui2)
      frame.pack(expand=True, fill=BOTH, padx=20, pady=20)
      # Create A Canvas
      my_canvas = Canvas(frame)
      my_canvas.pack(side=LEFT, fill=BOTH, expand=1)

# Add A Scrollbar To The Canvas
      my_scrollbar = ttk.Scrollbar(frame, orient=VERTICAL, command=my_canvas.yview)
      my_scrollbar.pack(side=RIGHT, fill=Y)

# Configure The Canvas
      my_canvas.configure(yscrollcommand=my_scrollbar.set)
      my_canvas.bind('<Configure>', lambda e: my_canvas.configure(scrollregion = my_canvas.bbox("all")))

# Create ANOTHER Frame INSIDE the Canvas
      second_frame = Frame(my_canvas)

# Add that New frame To a Window In The Canvas
      my_canvas.create_window((0,0), window=second_frame, anchor="nw")
      
      
      ///////////
      btn.pack()
      gui2.mainloop()    
          
gui = Tk()

gui.title('PythonApp')
gui.geometry("500x400")
label = Label(gui, text="Bienvenue ! Veuillez cocher votre choix",font= ('Helvetica 12 bold')).place(relx=.5, rely=.3,anchor= CENTER)

v = StringVar()
v.set(None) # initialiser

r1 = Radiobutton(gui, text=" Tube Nommé", variable=v, value="Tube", command=sel).place(anchor=CENTER, relx=.5, rely=.4)
r2 = Radiobutton(gui, text=" Sockets : TCP", variable=v, value="Sockets", command=sel).place(anchor=CENTER, relx=.5, rely=.5)

label = Label(gui)
label.pack()
gui.mainloop()
