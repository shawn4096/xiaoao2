// yaomiao.c

#include <ansi.h>

inherit ITEM;

int gf=0;
 
void create()
{
        set_name(HIG "药苗" NOR, ({"yao miao","miao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",
                "这是一株精品药苗，需要常常浇水(jiao)，否则容易干死，药苗甚是娇贵和脆弱，");
                set("unit", "株");
                set("no_get",1);
                set("5type","土");
                set("8type","乾");
                set("stime",0);
                set("location",1);
        }
}

void init()
{
        add_action("do_jiao","jiao");
                        
}

int do_jiao(string arg)
{
        object ob;
        object me=this_player();
     
        if(gf==0)
        {
                gf=1;
                call_out("grow", 10,me); 
        }
        if(!arg || !objectp(ob=present(arg, environment(me))))
                return notify_fail("地上没苗，你要浇什么？\n");
        if (ob->query("owner")!=me->query("id"))
			return notify_fail("这株苗不是你的，你不懂药性，无法浇水！\n");
		
		if (!me->query_temp("sld/zhongyao/yumiao"))
			return notify_fail("你育苗了么？？！\n");
		if((uptime()-ob->query("jtime"))>30)
        {
                call_out("destructing", 1, ob); 
				me->delete_temp("sld/zhongyao");
				//environment(this_object())->delete("zhongyao");
                return notify_fail("你已经一天多没浇水，药苗枯死了。\n");
        }
		else if((uptime()-ob->query("jtime"))<10)
        {
                return notify_fail("你刚浇过水了，等会儿再浇吧。\n");
        }

        ob->set("jtime",uptime());
        message_vision("$N浇了一瓢水，药苗又长高了些。\n",me);
        return 1;
}
void destructing(object ob)
{
        if(ob)
          destruct(ob);
}


void grow(object me)
{
        int times;
        object obj;
        object ob=this_object();
		if (!me) return;
	
        times=uptime()-query("stime");
        if(times>=120)
        {

                if(!objectp(obj=new(__DIR__"yaocao")))
                {
                        call_out("grow", 10,me);
                } 
                else
                {
						message_vision(HIM"在你勤快浇水培育下，药苗正在茁壮成长，已经成为成熟的药草!\n"NOR,me);
						message_vision(HIY"恭喜$N！"HIM+ob->query("8type")+HIG+ob->query("5type")+HIY"药性的药草培育成功了!\n"NOR,me);

                        obj->set("5type",query("5type"));
                        obj->set("8type",query("8type"));
                        obj->set("long",obj->query("long")+query("8type")+query("5type")+"性。\n");
						obj->set("owner",me->query("id"));
						obj->set("long",obj->query("long")+"这是一株由"+me->query("name")+"精心培育的药苗！\n");
                        obj->move(environment(this_object()));
                        call_out("destructing", 1, ob); 
						me->set_temp("sld/zhongyao/miaook",1);
						me->improve_skill("yaozhi",me->query_int());
						return;
                }
        }
        else if(times>=60)
        {
				message_vision(YEL"在你勤快浇水培育下，药苗正在茁壮成长，已经成为金黄的药苗!\n"NOR,me);
				me->improve_skill("yaozhi",me->query_int());
                set("name",YEL"金黄的药苗"NOR);
                call_out("grow", 60,me);   
        }
        else
        {
			message_vision(HIG"在你勤快浇水培育下，药苗正在茁壮成长，已经成为嫩青的药苗!\n"NOR,me);
			me->improve_skill("yaozhi",me->query_int());
            set("name",HIG"嫩青的药苗"NOR);
            call_out("grow", 30,me);   
        }
}