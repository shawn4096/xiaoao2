// lgxroom.c
// ½������
inherit ROOM;
void create()
{
	set("short","½������");
	set("long",@long
������������ɢ��½�����ļң������ı��Ϲ��˲����黭�����в�����ֵ
����֮���������֪�����˶Դ��ǻ����˴�����Ѫ���ŵ����ռ�����˶����
��֮����
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
	      if (ob[j]->query("name")=="½����"){
               ob[j]->move("/d/sld/lgxroom");			  
		      write("�����ϱ���һ���ˣ��޷��뿪��\n");
			  log_file("lgxbadmanlist", sprintf("%8s(%8s) �������½������ͼ���ߣ���¼�ڰ���\n",ob->name(1),ob->query("id")));
		      return 0;
	         }	
		
		
		me->delete_temp("yaozhong");
		me->delete_temp("makeyao");
		
		if (me->query("name")=="½����") return 0;		
	}
	return ::valid_leave(me, dir);
} 
