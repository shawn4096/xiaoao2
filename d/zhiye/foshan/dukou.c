
inherit ROOM;
void create()
{
        set("short", "佛山海港");
        set("long", @LONG
你迎着阵阵海风来到了港口，这里是一个已经被废弃了很久的港口。
     这个港口曾经繁荣过一段很长的时间，因为传说可去某座小岛得到
武功秘籍，许多武林人士蜂拥而至，而这里就是传说中的小岛航行的起点。
LONG);
	set("outdoors", "佛山");
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
	tell_object(me,"只见远远有个人想你打了个招呼，你定睛一看，正是那邀你来的中年男子。\n");
	tell_object(me,"那中年男子朗声笑道：还道你不敢来了呢，这就上船吧。\n");
	message_vision("$N略一沉吟，纵身跃上了搁浅在边上的小船。\n",me);
	me->move(DZD_D->query_boat());
	tell_room(environment(me),me->name()+"纵身跳了上来。\n",({me}));	
}
