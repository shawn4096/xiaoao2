// lgxroom.c
// 陆高轩家
inherit ROOM;
void create()
{
	set("short","陆府正厅");
	set("long",@long
这里是神龙教散人陆高轩的家，屋内四壁上挂了不少书画，其中不乏价值
连城之作，可想而知，主人对此是花费了大量心血，才得以收集到如此多的名
贵之作。
long);
	set("exits",([
	    "north" : __DIR__"lgxws",
         "east" : __DIR__"lgxys",
         "out" : __DIR__"kongdi",
		"west" : __DIR__"lianyaoshi",
]));
       set("objects",([
		__DIR__"npc/lgx" : 1,
]));
	set("coor/x",490);
  set("coor/y",410);
   set("coor/z",10);
   //set("no_clean_up", 0);
   setup();
}
	    	
int valid_leave(object me, string dir)
{
	object *ob;
	int j;
	if (dir == "out")
	{
		ob = deep_inventory(me);
		 j = sizeof(ob);
	       while (j--)
	      if (ob[j]->query("name")=="陆高轩"){
               ob[j]->move("/d/sld/lgxroom");			  
		      write("你身上背负一个人，无法离开。\n");
			  log_file("lgxbadmanlist", sprintf("%8s(%8s) 恶意打晕陆高轩企图背走，记录在案。\n",ob->name(1),ob->query("id")));
		      return 0;
	         }	
		
		
		me->delete_temp("yaozhong");
		me->delete_temp("makeyao");
		
		if (me->query("name")=="陆高轩") return 0;		
	}
	return ::valid_leave(me, dir);
} 
