import subprocess
from tkinter import *
from tkinter import ttk
import os
import time


def client_tube(second_frame):
   Commande="\" ../tube_nomme/client >> ClientsTubeNomme.txt.txt; exec bash\""
   subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande}",shell=True)
   time.sleep(3)
   f = open("ClientsTubeNomme.txt")
   lines=f.readlines()
   for line in lines:
      temp_text = line
      Label(second_frame, text=temp_text).pack()
   f.close()
   os.remove("ClientsTubeNomme.txt")

def client_socket(gui2,e):
                
   nb=int(e.get())   
   #create new window
   gui3 = Toplevel(gui2)
   gui3.geometry("650x450")  
   # Add image file
   bg = PhotoImage(file = "img.png")
   label1 = Label( gui3, image = bg)
   label1.place(x = 0, y = 0)

   frame = Frame(gui3,bg="#4a6f7c")
   frame.pack(expand=True, fill=BOTH, padx=20, pady=20)
   # Create A Canvas
   my_canvas = Canvas(frame,bg="#4a6f7c")
   my_canvas.pack(side=LEFT, fill=BOTH, expand=1)

   # Add A Scrollbar To The Canvas
   my_scrollbar = ttk.Scrollbar(frame, orient=VERTICAL, command=my_canvas.yview)
   my_scrollbar.pack(side=RIGHT, fill=Y)

   # Configure The Canvas
   my_canvas.configure(yscrollcommand=my_scrollbar.set)
   my_canvas.bind('<Configure>', lambda e: my_canvas.configure(scrollregion = my_canvas.bbox("all")))

   # Create ANOTHER Frame INSIDE the Canvas
   second_frame = Frame(my_canvas,bg="#4a6f7c")  
   #my_canvas.create_image((0,0), image=bg, anchor="nw")
   my_canvas.create_window((0,0), window=second_frame, anchor="nw")  

   
   for i in range(nb):
      Commande="\" ../Sockets/client >> ClientsSockets.txt; exec bash\""
      subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande}",shell=True)
      time.sleep(3)
      f = open("ClientsSockets.txt")
      Label(second_frame, text="Client "+str(i+1),bg="#4a6f7c",fg="#760523",font= ('Helvetica 15 bold underline')).pack()

      lines=f.readlines()
      for line in lines:
         temp_text = line
         Label(second_frame, text=temp_text,bg="#4a6f7c",font= ('italic 11 bold')).pack()
      f.close()
      os.remove("ClientsSockets.txt")
   gui3.mainloop()    

def sel():
   if v.get()=="Tube":
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

      Commande1="\" ../tube_nomme/server; exec bash\""
      subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande1}",shell=True)     

      btn = Button(gui2, text ="Lancer un Client",command=lambda:client_tube(second_frame))
      btn.pack()
      gui2.mainloop()
      
   if v.get()=="Sockets":
      gui2 = Toplevel(gui)
      gui2.geometry("650x450")
      bg = PhotoImage(file = "img.png")
      label1 = Label( gui2, image = bg)
      label1.place(x = 0, y = 0)
   
      l = Label(gui2, text = "Veuillez entrer le nombre de clients que vous désirez l'exécuter",bg="#4a6f7c",font= ('Helvetica 12 bold')).place(relx=.5, rely=.3,anchor= CENTER)
      e = Entry(gui2, bd = 5)
      e.pack(pady= 155)
      Commande1="\" ../Sockets/server; exec bash\""
      subprocess.Popen(f"gnome-terminal --tab -- bash -c {Commande1}",shell=True)
      btn = Button(gui2, text ="Lancer",fg="#00222d",font= ('Helvetica 12 bold'),command=lambda:client_socket(gui2,e)).place(anchor=CENTER, relx=.5, rely=.5)
      gui2.mainloop()
          
gui = Tk()

gui.title('Application Client_Serveur')
gui.geometry("500x400")
bg = PhotoImage(file = "img.png")
label1 = Label( gui, image = bg)
label1.place(x = 0, y = 0)
label = Label(gui, text="Bienvenue ! Veuillez cocher votre choix",bg="#4a6f7c",font= ('Helvetica 12 bold')).place(relx=.5, rely=.3,anchor= CENTER)

v = StringVar()
v.set(None)

r1 = Radiobutton(gui, text=" Tube Nommé",bg="#4a6f7c", variable=v, value="Tube", command=sel).place(anchor=CENTER, relx=.5, rely=.4)
r2 = Radiobutton(gui, text=" Sockets : TCP",bg="#4a6f7c" ,variable=v, value="Sockets", command=sel).place(anchor=CENTER, relx=.5, rely=.5)

#label = Label(gui)
#label.pack()
gui.mainloop()
