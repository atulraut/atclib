Polymorphism Implementation using C
------------------------------------------

Call Flow -->
<<<<<<< HEAD
1] main ()--> main.c
2] base_init    --> base_init.c
3] at_list[] array init--> public.h
4] at_list[i].handle->init () --> public.h
                                    This will call individual plug-in init functions.

public.h  --> Base Class, all the classes must derived from this class.
plug-01.c --> Derived class.
plug-02.c --> Derived class.
      Both this classes derived from at_base_type (define in public.h)
=======
1] main ()			--> main.c 
2] base_init		    	--> base_init.c
3] at_list[] array init		--> public.h
4] at_list[i].handle->init () 	--> public.h 
                                    This will call individual plug-in init functions. 

public.h  --> Base Class, all the classes must derived from this class.
plug-01.c --> Derived class.
plug-02.c --> Derived class. 
	      Both this classes derived from at_base_type (define in public.h)
>>>>>>> cdcc9cc1003f5e747cb576f6e63447c095ec6fa2

