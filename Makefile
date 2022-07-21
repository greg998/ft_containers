# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiquiau <ggiquiau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 13:08:22 by ggiquiau          #+#    #+#              #
#    Updated: 2022/07/21 13:35:21 by ggiquiau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix tests/, \
								main.cpp \
								Tester.cpp \
								UnitTest.cpp \
)

NAME_FT = ft
NAME_STD = std
NAME_CMP = cmp
	
OBJS_FT            = ${SRCS:tests%.cpp=${OBJS_DIR}/$(NAME_FT)%.o}
OBJS_STD            = ${SRCS:tests%.cpp=${OBJS_DIR}/$(NAME_STD)%.o}
OBJS_CMP            = ${SRCS:tests%.cpp=${OBJS_DIR}/$(NAME_CMP)%.o}

OBJS_DIR		= tests/objs

HEADERS			= $(addprefix includes/, vector.tpp iterator.tpp  iterator_traits.tpp random_access_iterator.tpp algorithm.tpp type_traits.tpp utility.tpp map.tpp) $(addprefix tests/, Tester.hpp UnitTest.hpp)

CXX  			=  c++

CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -Iincludes -Itests

RM 				= rm -f


${OBJS_DIR}/$(NAME_FT)/%.o:	tests/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)/$(NAME_FT)
					${CXX} -c ${CXXFLAGS} -DNS=\"$(NAME_FT)\" -o $@ $<

${OBJS_DIR}/$(NAME_STD)/%.o:	tests/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)/$(NAME_STD)
					${CXX} -c ${CXXFLAGS} -DNS=\"$(NAME_STD)\" -o $@ $<
					
${OBJS_DIR}/$(NAME_CMP)/%.o:	tests/%.cpp ${HEADERS}
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)/$(NAME_CMP)
					${CXX} -c ${CXXFLAGS} -DNS=\"$(NAME_CMP)\" -DCMP=1 -o $@ $<

all: $(NAME_FT) $(NAME_STD) $(NAME_CMP)


$(NAME_FT):		$(OBJS_FT)
		${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJS_FT} -o $@

$(NAME_STD):	$(OBJS_STD)
		${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJS_STD} -o $@

$(NAME_CMP):	$(OBJS_CMP)
		${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJS_CMP} -o $@
				
clean:
				${RM} ${OBJS_FT} ${OBJS_STD} ${OBJS_CMP}
				@rm -fd ${OBJS_DIR}/$(NAME_FT) || true
				@rm -fd ${OBJS_DIR}/$(NAME_STD) || true
				@rm -fd ${OBJS_DIR}/$(NAME_CMP) || true
				@rm -fd ${OBJS_DIR} || true

fclean:			clean
				${RM} $(NAME_FT) $(NAME_STD) $(NAME_CMP)
				
re:
				${MAKE} fclean
				${MAKE} all

.PHONY:			all clean fclean re
