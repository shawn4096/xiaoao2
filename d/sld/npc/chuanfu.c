//wzfeng 98 10 13
//chuanfu.c
inherit NPC;
#include <ansi.h>

int ask_chuhai();
void create()
{
	set_name("����",({ "chuan fu","chuan","fu"}));
	set("long", "����һ���ϴ���ר�Ÿ�����������ȥ��ԭ�Ĵ�ֻ��\n");
	set("gender", "����");
	set("attitude", "friendly");
	set("no_get_from", 1);
	set("unique", 1);
        set("age", 55);

	    set("per",15);
        set("shen", 0);
        set("str", 130);
        set("int", 125);
        set("con", 127);
        set("dex", 129);

        set("max_qi", 50000); 
        set("max_jing", 30000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jingli", 20000);
        set("eff_jingli", 20000);
        set("jiali", 10);
        set_skill("unarmed", 800);
        set_skill("dodge", 800);
		set_skill("taiji-quan",800);
        set_skill("cuff", 800);
		map_skill("cuff","taiji-quan");
        prepare_skill("cuff","taiji-quan");
        
	    set("combat_exp", 50000000);
    	create_family("������",3, "����");

        set("inquiry", ([
		"chuhai" : (: ask_chuhai :),
		"����" : (: ask_chuhai :),
	]));
        
	setup();
}

void init()
{
	::init();
	if(!objectp(find_object("/d/sld/md1"))) {
		load_object("/d/sld/md1");   
	}
}

int ask_chuhai()
{
	command("say �������������ͨ�������Ҳ��ܷ��ɴ�ֻ,��Ȼ�κ��˲��������뵺������");
	return 1;
}

int accept_object(object who, object ob)
{
	if( ((string)ob->query("id") != "ling pai") || ob->query("sld") !=1 )
		return 0;
    //if (this_player()->query_temp("sld/givelp"))
         //return notify_fail(CYN"�������˵���������Ѿ��������ƣ����ǵȻ���˵�ɡ���\n"NOR);
	//�뿪ԭλʧЧ
	if ( file_name(environment(this_object())) != this_object()->query("startroom")) 
		return notify_fail(CYN"�������˵���������ǵ��һص���������˵�ɡ���\n"NOR);
//�ȴ�ʱ��5
	    who->start_busy(5);
		
		//this_player()->add_temp("sld/givelp",1);
		//this_player()->move("/d/sld/haitan");
	    remove_call_out("go_chuan");
        
		call_out("go_chuan", 0,who,ob);
        
	    call_out("destructing", 0, ob); //ȡ������
        
	    return 1;
}

void destructing(object ob)
{
	destruct(ob);
}

void go_chuan(object me,object ob)
{
	object fchuan;	
	int i;
	string *fcname=({ __DIR__"obj/fc1",__DIR__"obj/fc2",__DIR__"obj/fc3" ,__DIR__"obj/fc4",__DIR__"obj/fc5",__DIR__"obj/fc6",__DIR__"obj/fc7",__DIR__"obj/fc8",__DIR__"obj/fc9", });
//Ѱ�ҿ��еĴ�ֻ
	for(i=0;i<sizeof(fcname);i++){
		if(!objectp(fchuan=find_object(fcname[i])))
			fchuan=load_object(fcname[i]);
		if(fchuan->query_temp("curstatus",1)!="run")
		   break;
	}
	//�������ȴ�
	if(i>=sizeof(fcname)){
		command("say ����û�������һ��ɡ�\n");
		remove_call_out("go_chuan");
		call_out("go_chuan", 2,me); 
		return;
	}
	command("say ��Ȼ��������ͨ�����ƣ�����ʹ����ϴ���");
	if(fchuan->query_temp("curstatus",1) == "ready") {
		message_vision("\nֻ��$N���ϴ��˸����ƣ��ƺ���ʲô���š�\n",this_object());
		message_vision("��һ�����һ��С�����Ӻ��ϻ���ʻ����\n\n", this_object());
		message_vision(CYN"$N��$n˵���������Ϸ��һ��С�ģ���\n"NOR, this_object(),me);
		fchuan->set_temp("curstatus","ready2");
	}
	message_vision("$N����һԾ������С����\n",me);
	me->move(fcname[i]);	
	tell_room(environment(me), me->name() + "Ծ�ϴ�����\n", ({ me }));
	
		//call_out("destructing", 0, ob); 
	//me->delete_temp("sld/givelp");
}
