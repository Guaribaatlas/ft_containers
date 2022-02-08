# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 11:57:14 by vneirinc          #+#    #+#              #
#    Updated: 2022/02/08 11:08:20 by jehaenec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FTNAME		=	ft_test
STDNAME		=	std_test
FTSPEED		=	ft_speed
STDSPEED	=	std_speed

RM			=	rm -f

test: all
	./$(FTNAME) > ftres && ./$(STDNAME) > stdres && diff ftres stdres
	$(RM) ftres stdres

all: ft std

ft: $(FTNAME)

std: $(STDNAME)

$(FTNAME):
	$(MAKE) -f compile.mk MORE="-DNOPRINT" NAME=$@ MAIN="main.cpp"

$(STDNAME):
	$(MAKE) -f compile.mk NAME=$@ MORE="-DNAMESPACE=std" MAIN="main.cpp"

speed: $(FTSPEED) $(STDSPEED)

$(FTSPEED):
	$(MAKE) -f compile.mk speed NAME=$@ MORE="-DNOPRINT" MAIN="speed.cpp"

$(STDSPEED):
	$(MAKE) -f compile.mk speed NAME=$@ MORE="-DNAMESPACE=std -DNOPRINT" MAIN="speed.cpp"

clean:
	$(MAKE) -f compile.mk clean
	$(RM) $(STDNAME) $(FTNAME) $(STDSPEED) $(FTSPEED) ftres stdres

.PHONY:	all speed clean
