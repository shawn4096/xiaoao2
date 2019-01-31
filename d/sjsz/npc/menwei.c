
inherit NPC;

void create()
{
        set_name("门卫", ({ "men wei", "menwei"}) );
        set("gender", "男性" );
        set("age", 26);
        set("unique", 1);        
        set("long", "这位一个不苟言笑的门卫。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("per", 30);
        set("chat_chance", 25);
        set("chat_msg", ({
"门卫说道：“没有试剑令，不可进入山庄。”\n",
        }) );
        setup();
        carry_object(ARMOR_D("skirt1.c"))->wear();
}

int accept_object(object who, object ob)
{
        
        if (ob->query("id")=="shijian ling" && ob->query("id")) 
        {
                tell_object(who, "门卫点头说道：“请进山庄吧！”\n");
                who->set_temp("get_in_sjsz",1);
                return 1;
        }
		else
		{
			tell_object(who, "门卫一皱眉说道：“这是何物！”\n");			
		}
        return 0;
}
