SOCKET_SRC_DIR := Sockets/src
SOCKET_EXEC_DIR := Sockets/executables
TUBE_SRC_DIR := tube_nomme/src
TUBE_EXEC_DIR := tube_nomme/executables
SRC_FILES := $(wildcard $(SOCKET_SRC_DIR)/*.c)
CFLAGS := -g


all: app 

app: $(SRC_FILES:$(SOCKET_SRC_DIR)/%.c=$(SOCKET_EXEC_DIR)/%) ServeurTube ClientTube
	python3 interface/interf.py

ServeurTube: $(TUBE_SRC_DIR)/Serveur.c $(TUBE_SRC_DIR)/Handlers_Serv.c
	@mkdir -p $(TUBE_EXEC_DIR)
	gcc $(CFLAGS) -o $(TUBE_EXEC_DIR)/Serveur $(TUBE_SRC_DIR)/Handlers_Serv.c $(TUBE_SRC_DIR)/Serveur.c

ClientTube: $(TUBE_SRC_DIR)/Client.c $(TUBE_SRC_DIR)/Handlers_Cli.c
	@mkdir -p $(TUBE_EXEC_DIR)
	gcc $(CFLAGS) -o $(TUBE_EXEC_DIR)/Client $(TUBE_SRC_DIR)/Handlers_Cli.c $(TUBE_SRC_DIR)/Client.c
	
$(SOCKET_EXEC_DIR)/%: $(SOCKET_SRC_DIR)/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $< -o $@


clean:
	rm -rf $(TUBE_EXEC_DIR)
	rm -rf $(SOCKET_EXEC_DIR)