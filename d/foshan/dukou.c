
inherit ROOM;
void create()
{
        set("short", "��ɽ����");
        set("long", @LONG
��ӭ�����󺣷������˸ۿڣ�������һ���Ѿ��������˺ܾõĸۿڡ�
     ����ۿ��������ٹ�һ�κܳ���ʱ�䣬��Ϊ��˵��ȥĳ��С���õ�
�书�ؼ������������ʿ��ӵ��������������Ǵ�˵�е�С�����е���㡣
LONG);
	set("outdoors", "��ɽ");
	set("no_fight",1);
	set("exits",([
		"north" : __DIR__"shulin_dzd",
		//"southwest" : "d/xiakedao/xkroad3",			
"east" : "/d/foshan/haibin",   
	]));	
	setup();
}

#define DZD_D "/d/foshan/dzdd.c"

void init()
{
	object me;
	mapping job;
//    add_action("do_go", "qu");
	me= this_player();
	if(mapp(job = me->query_temp("job_dzd"))){
		if(job["asked"]==1 && !job["ready"] && DZD_D->is_player(me) )			
			call_out("move_to_boat",random(3)+1,me);		
	}
}

void move_to_boat(object me)
{
	mapping job;
	
	if(!DZD_D->is_player(me)) return;	
	if(!mapp(job = me->query_temp("job_dzd"))) return;	
	if(job["asked"]!=1 || job["ready"]==1 ) return;	
	//tell_object(me,file_name(environment(me))+"      "+__FILE__+"\n" );
	if(file_name(environment(me))+".c"!=__FILE__) return;
	if(environment(me)!=this_object()) return;
	job["ready"]=1;
	map_delete(job,"asked");
	DZD_D->player_ready(me);
	tell_object(me,"ֻ��ԶԶ�и���������˸��к����㶨��һ�������������������������ӡ�\n");
	tell_object(me,"��������������Ц���������㲻�������أ�����ϴ��ɡ�\n");
	message_vision("$N��һ����������Ծ���˸�ǳ�ڱ��ϵ�С����\n",me);
	me->move(DZD_D->query_boat());
	tell_room(environment(me),me->name()+"��������������\n",({me}));	
}
