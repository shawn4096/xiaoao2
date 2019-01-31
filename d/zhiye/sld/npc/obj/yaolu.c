// yaolu.c

#include <ansi.h>

inherit ITEM;

//#define MAXS 2160
#define MAXS 300
void yao_id(string arg,object yao);
void yao_name(string arg,object yao);
void yao_long(string arg,object yao);
int do_fail();
void qiangjie(object me,int i);
void init()
{
        add_action("do_open", "open");
        add_action("do_fang", "fang");

         add_action("do_pour", "pour"); //��ˮ
       add_action("do_close", "close");
        add_action("do_fire", "dianhuo");
        add_action("do_lianyao", "lianyao");
        add_action("do_miehuo", "miehuo");
        add_action("do_kanyao", "kanyao");
        add_action("do_qingsao", "qingsao");

		add_action("do_qu", "qu");
        add_action("do_quyao", "quyao");
       // add_action("do_get","get");
        add_action("do_put","put");
}

void create()
{
        set_name(HIG "ҩ¯" NOR, ({"yao lu","lu"}));
        set_weight(3000000);
		set_max_encumbrance(2000);

		if (clonep())
                set_default_object(__FILE__);
        else {
                      

				set("long",
                "����һֻ������ҩ��¯�ӣ�����\n"
				+HIY"��(open)¯�ǡ���(fang)ҩ�ģ���ˮ(pour ),�ر�(close)\n"
				+"���(dianhuo)¯��,��ҩ(lianyao),ȡ(qu)ҩ�ģ���(kan)¯�ӣ�\n"
				+"ȡ(quyao)ҩ,����ҩʧ�ܿ�����ɨ(qingsao)��\n"NOR);
                set("unit", "ֻ");
                set("no_sell",1);
                set("yaocai",0);
                set("zhuyao",0);
                set("location",1);
				set("no_get",1);
				set("no_steal",1);
				set("no_give",1);
        }
}
int is_container() { return 1; }

//���ٷ�����

void qiangjie(object me,int i)
{
        object xm;
        object ob=this_object();
		int j,skill;
		string *skills;

        if(!ob)
           return;
        
		//me=ob->query("owner");
        me=this_player();
		
		skills=me->query_skill();

		if(!me)
        {
                call_out("destructing", 1, ob); 
                return;
        }
        //if(objectp(xm=me->query_temp("lianyao/rumo")))
          //      destruct(xm);
        
		xm=new("/d/sld/npc/xinmo");
        if(!objectp(xm))
        {
                me->delete_temp("lianyao/rumo");
                call_out("qiangjie",60);
                return;
        }
		if (i>2)
		{
			xm->set("combat_exp",(int)me->query("combat_exp")*3/2);
			skill=me->query("max_pot")-70+random(10);
		}else if (i>1)
		{
			xm->set("combat_exp",me->query("combat_exp"));
			skill=me->query("max_pot")-20;
		}else {
			xm->set("combat_exp",(int)me->query("combat_exp")*2/3);
			skill=me->query("max_pot")-100;
		}
        
        xm->set("str", me->query_str());
        xm->set("int", me->query_int());
        xm->set("con", me->query_con());
        xm->set("dex", me->query_dex()+me->query_dex()/3);
        xm->set("kar", me->query_kar());
        xm->set("max_qi",me->query("max_qi")+me->query("max_qi")/2);
        xm->set("qi",xm->query("max_qi"));
		xm->set("eff_qi",xm->query("max_qi"));

        xm->set("max_jing",me->query("max_jing")+me->query("max_jing")/2);
        xm->set("jing",xm->query("max_jing"));
		xm->set("eff_jing",xm->query("max_jing"));

        xm->set("max_neili",me->query("max_neili"));
        xm->set("neili",xm->query("max_neili")*2);
        xm->set("eff_jingli",me->query("eff_jingli")+me->query("eff_jingli")/3);
        xm->set("jingli",xm->query("eff_jingli")*2);
        xm->set_skill("dodge", me->query_skill("dodge",1)/2+me->query_skill("dodge"));
        xm->set_skill("parry", me->query_skill("parry",1)/2+me->query_skill("parry"));
        xm->set("name",me->name(1)+"����ħ");
        
		//xm->set("id",me->query("id")+"'s xinmo");

		xm->set("long",me->query("long")+"\n����"+xm->query("name")+"���û�����ħ��\n");
        xm->set("gender",me->query("gender"));
        xm->set("title", me->query("title"));   
        xm->set("age", me->query("age"));
        xm->set("owner",me);
		/*
		for (j=0;j>=sizeof(skills);j++ )
		{
			xm->set_skill(skills[j],skill);
		}*/
        me->set_temp("lianyao/rumo",xm);
        xm->move(environment(this_object()));
        me->kill_ob(xm);
        xm->kill_ob(me);
        message_vision("$N���ճ�ʱ�������ҩ��֮�У���㱼��Ȼ����$n��$N��Ȼ���������ɵô��һ����\n",me,xm);
		//�������κ��ٳ���
		//if (i>2) return;
		//call_out("qiangjie",10+random(10),me,i+1);
		
		return;
}
       
void destructing(object ob)
{
        if(ob)
                destruct(ob);
}
//ȡҩ
int do_get(string arg)
{
        string temp,obj;
        object yl;
        object me = this_player();
        object ob=this_object();

        if(arg)
        {
                if(arg=="all" || arg=="ALL")
                        return 1;
				if (!ob->query("lianyao/open"))
				{
					return notify_fail("¯����δ�򿪣������ȡ������\n");
				}
				if(ob==present(arg, environment(ob)))
                {
                        if(query("zhuyao"))
                                return notify_fail("ҩ¯���ڰ���ҩ����ܰᶯ������ҩ��¯�ӡ�\n");
                }
                else
                {
				if(sscanf(arg,"%s from %s",temp,obj)==2)
                        {
                                if(objectp(yl=present(obj, me))||
                                   objectp(yl=present(obj, environment(me))))
                                {
                                        if(yl==ob)
                                                return notify_fail("ֻ�ܴ�ҩ¯��ȡ(qu)������\n");
                                }
								//ȡ��һ����Ҫ��ӱ��
                        }
                }
        }
        return 0;
}
//����ҩ��
int do_put(string arg)
{
        string temp,obj;
        object yl;
        object me = this_player();
	

        if(arg)
        {
                if(sscanf(arg,"%s in %s",temp,obj)==2)
                {
                        if(objectp(yl=present(obj, me))||
                           objectp(yl=present(obj, environment(me))))
                        {
                                if(yl==this_object())
                                        return notify_fail("ֻ����ҩ¯���(fang)������\n");
                        }
                }
        }
		if (!yl->query("lianyao/open"))
		{
			return notify_fail("¯����δ�򿪣������ȡ������\n");
		}
        return 0;
}
//��ɨ¯��
int do_qingsao(string arg)
{
	object ob,me;
	me=this_player();
	ob=this_object();
	if (!arg||arg!="lu")
	{
		return notify_fail("��Ҫ��ɨʲô��\n");
	}
	if (!me->query_temp("lianyao"))
	{
		return notify_fail("����δ�������÷����ɣ���Ҫ���ң�\n");
	}
	ob->delete_temp("lianyao");
	ob->delete("lianyao");
	ob->delete_temp("liquid");

	message_vision(WHT"$N������ʼ��ɨҩ¯��һ�Ὣҩ¯��ɨ�ɾ���\n"NOR,me);
	return 1;
}
//��¯�� 1
int do_open(string arg)
{
	    object me = this_player();
        object yc;
		if(!arg)
           return notify_fail("��Ҫ�򿪿���ô��\n");
        if (arg!="ҩ¯"&&arg!="lu")
        {
			return notify_fail("��Ҫ�򿪵Ķ�����ʲô��\n");
        }
		//����
        if (this_object()->query("lianyao/open"))
        {
			return notify_fail("¯���Ѿ�����!\n");
        }
		//��ҩ��,
        if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"ҩ¯����");
			return notify_fail("¯��������ҩ�У��㱻�������ˣ�\n");
        }

		if (me->is_busy()||me->is_fighting())
		{
		
			return notify_fail("��������æ�����У���Ͼ���ǣ�\n");
       
		}
	
        message_vision(HIY+"\n$N"+HIY+"��ҩ¯�ĸ�����򿪡�\n"NOR,me);
		
		//me->set_temp("lianyao/open",1);
		this_object()->set("lianyao/open",1);
		//this_object()->set("lianyao/doing", 1);  

		me->add_busy(1);
        return 1;       

}
//��ҩ�� 2
int do_fang(string arg)
{
        object me = this_player();
        object yc;
		if(!arg)
                return notify_fail("��Ҫ��ʲô��ҩ¯��ȥ��\n");
        if(!objectp(yc=present(arg, me)))
                return notify_fail("������û��"+arg+"���ֶ�����\n");
        if(!this_object()->query("lianyao/open"))
                return notify_fail("¯����δ�򿪣��㲻�ܷ�"+yc->query("name")+"��ҩ¯��ȥ��\n");
		if(yc->query("id")!="yao cao")
                return notify_fail("�㲻�ܷ�"+yc->query("name")+"��ҩ¯��ȥ��\n");
        if(query("yaocai")>=9)
                return notify_fail("ҩ¯���ž���ҩ�ݣ������Ѿ���ҩ�������ˡ�\n");
        
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"ҩ¯����");
			return notify_fail("¯��������ҩ�У��㱻�������ˣ�\n");
        }

		message_vision(HIY+"\n$N"+HIY+"��һ��"+yc->query("name")+HIY"�Ž�ҩ¯��\n"NOR,me);
        yc->move(this_object());
        yc->set("stime",uptime());
        //����ҩ�ݱ��
		add("yaocai",1);
        //set("zhuyao",1);
		
        return 1;       
}
//��ˮ 3
int do_pour(string arg)
{
        string hehe, what;
        object me, ob, obj;
        me = this_object();
        ob = this_player();
        
		if( !arg
        ||  sscanf(arg, "%s to %s", hehe, what) != 2)
                return notify_fail("����<pour ���� to lu>����ˮ�Ž���ҩ¯��\n");

        if( ob->is_busy() ) 
                return notify_fail("����æ���ء�\n");

        if( ob->is_fighting() )
                return notify_fail("������ս���У�\n");

        if( !me->query("lianyao/open") )
                return notify_fail("��¯�ĸ���û�д򿪡�\n");

        if( !objectp( obj = present(hehe, ob)))   // ��������ϵ���Ʒ��ID���ԣ���������¯���ˮ��
                return notify_fail("������û��"+hehe+"���������ҩ¯���ˮ��\n");
                
        if( !obj->query("liquid/type"))           // ��������ϵ���Ʒ����ʢˮ�����󣬲�������¯���ˮ��
                return notify_fail(obj->name()+"����ʢˮ������\n");

        if( !obj->query("liquid/remaining") )     // �ж�������ʢˮ���������Ƿ���ˮ��
                return notify_fail(obj->name() + "�����Ѿ�һ�β�ʣ�ˡ�\n");
        
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"ҩ¯����");
			return notify_fail("¯��������ҩ�У��㱻�������ˣ�\n");
        }

        message_vision("$N��һЩ"+ obj->query("liquid/name") +"��"+ obj->name() +"������ҩ¯��\n", ob);
        obj->add("liquid/remaining", -1);
        //¯�ӱ��
		me->add_temp("liquid/remaining", 1);
        me->set_temp("liquid/name", obj->query("liquid/name"));
        return 1;
}
//ȡҩ��,ҩ�ݷŴ����Ա����
int do_qu(string arg)
{
        object me = this_player();
        object yc,yl;

        if(!arg)
                return notify_fail("��Ҫ��ҩ¯����ʲô������\n");
      
        yl=this_object();
        if(!objectp(yc=present(arg, yl)))
                return notify_fail("ҩ¯��û��"+arg+"���ֶ�����\n");
        if(yc->query("id")!="yao cao")
                return notify_fail("�㲻�ܴ�ҩ¯����"+yc->query("name")+"��\n");
        if( !yl->query("lianyao/open") )
                return notify_fail("��¯�ĸ���û�д򿪣��޷�ȡ������\n");
		if (this_object()->query("lianyao/fired")||this_object()->query("lianyao/doing"))
        {
			me->receive_wound("qi",(int)me->query("max_qi")/3,"ҩ¯����");
			return notify_fail("¯��������ҩ�У��㱻�������ˣ�\n");
        }

		message_vision(HIY+"\n$N"+HIY+"��ҩ¯���ó���һ��ҩ�ݡ�\n"NOR,me);
        
		yc->add("times",uptime()-yc->query("stime"));
        yc->move(me);
        add("yaocai",-1);
        if(query("yaocai")<=0)
                set("zhuyao",0);        
        

		return 1;       
}
//�Ǹ�
int do_close(string arg)
{
        object me, ob;
        me = this_object();
        ob = this_player();
        
        if( ob->is_busy() ) 
                return notify_fail("����æ���ء�\n");

        if( ob->is_fighting() )
                return notify_fail("������ս���С�\n");

        if( !arg || arg == "" || arg != "lu")
                return notify_fail("��Ҫ��ʲô��\n");

        if( !me->query("lianyao/open") )      // �жϴ�ʱ��¯�ĸ����Ǵ򿪻��ǹ��ϵ�
                return notify_fail("��¯�ĸ����Ѿ����ϡ�\n");

		if( arg == "lu" )
        {
          message_vision(HIC"$N������ŵĽ���¯�ĸ��Ӹ��ϡ�\n"NOR, ob);
          me->delete("lianyao/open");           // ������˰ѵ�¯�ĸ��ӹ��ϣ���ôȥ���˱�ǡ�
		  
          return 1;
        }

}
//���
int do_fire(string arg)
{
        object obj;
        object me = this_object();
        object ob = this_player();
        object *inv;
        inv = deep_inventory(me);

        if( ob->is_busy() ) 
                return notify_fail("����æ���ء�\n");

        if( ob->is_fighting() )
                return notify_fail("������ս���С�\n");

        if( me->query_temp("lianyao/open") )
                return notify_fail("��¯�ĸ���û�и��ϡ�\n");
        
        if( !objectp( obj = present("fire", ob)))   // �ж���������Ƿ��л��ۡ�
                return notify_fail("����Ҫһ�����ۡ�\n");
                
        if( (int)ob->query("neili")  <= 1000 )
                return notify_fail("������������������˻�Ҳ���������䡣\n");           
                
        if( (int)ob->query("max_neili")  <= 1500 )
                return notify_fail("������������������˻�Ҳ���������䡣\n");                           

        if( me->query_temp("lianyao/fired"))
                return notify_fail("����Ѿ��������ˡ�\n");   
                
        if(!me->query_temp("liquid/name") ||me->query_temp("liquid/name")!="��ˮ")
                return notify_fail("��¯��û��ˮ��ҩ�ݻᱻ������\n");  
                
        if( !sizeof(inv)) 
                return notify_fail("��¯����ʲô��û�С�\n");
                
        message_vision(HIR"\n$N��ȼҩ¯����Ĳ�𣬻��罥���ش���������\n"NOR, ob);
        //destruct(obj);
		//��� && ��ҩ����
        me->set("lianyao/fired", 1);
       // me->set("lianyao/doing", 1);
        ob->set_temp("lianyao/doing", 1);//���ڰ�ҩ
        ob->add_busy(1);
//���ҩ¯״��
		//remove_call_out("do_check");
    //    call_out("do_check", 300);//û�в���ob,ҩ�ɹ����ɹ�������޹�
        return 1;
}
//��ҩ����
int do_lianyao()
{
	object ob,me;
	int num;
	me=this_player();
	ob=this_object();
	if (!me) return 0;
	num=(int)ob->query("lianyao/marks",1);

	if (me->query("neili")<2500)
	{
		return notify_fail("�����������2500,�޷���ҩ��\n");
	}
	if (me->query("jingli")<2500)
	{
		return notify_fail("��ľ�������2500,�޷���ҩ��\n");
	}
	message_vision(GRN"\n$N�����ڹ��ĵ�����¯�����������ע����ʼ����ҩ�\n"NOR,me);
	
	if (!ob->query("lianyao/fired"))
	{
		return notify_fail("��û�е�������ҩ��\n");
	}
	if (!ob->query("yaocai"))
	{
		return notify_fail("ҩ¯��û��ҩ�ݣ������ҩ��\n");
	}
	if (random(num)<2+random(3))
	{
		if (!ob->query_temp("liquid/remaining")||ob->query_temp("liquid/name")!="��ˮ")
		{
			
			return do_fail();
		}
		
		switch (random(8))
		{
			case 0:
				tell_object(me,YEL"\n¯��������¯�²������ߣ�ҩ��������\n"NOR);
				ob->add("lianyao/marks",1);
				break;
			case 1:
				tell_object(me,MAG"\nһ��ҩ��Ѱ��ҩ¯��϶͸�˳����������Ŀ�������\n"NOR);
				ob->add("lianyao/marks",1);
				break;
			case 2:
				tell_object(me,BLU"\n��Ȼ��һ�ɻ�����ͣ�������ζ��������\n"NOR);
				tell_object(me,HIY"���д󼱣���æ�����ڹ����ƻ������ͷ��\n"NOR);

				ob->add("lianyao/marks",-1);
			
				break;
			case 3:
				tell_object(me,HIM"\nҩ�����ƣ�������������ͷ�����Ѳ��٣�\n"NOR);
				ob->add("lianyao/marks",2);
				break;
			case 4:
				tell_object(me,HIB"\nҩ¯�е�ҩ�ƺ�����Щ����ȳ���Ϣ���ƺ���Щ��ζ��\n"NOR);
				ob->add("lianyao/marks",-2);
				break;
			case 5:
				tell_object(me,WHT"\n�������ģ�ҩ¯�е�ҩ�����ڻ����ںϣ��ƺ������۵����ƣ�\n"NOR);
				ob->add("lianyao/marks",1);
				me->improve_skill("zhiyao",(int)me->query_int(1)/2);
				break;
			default:
				tell_object(me,HIW"\n�������ģ����Ҳ���ܷ��ģ�\n"NOR);
				ob->add("lianyao/marks",1);
				break;
		}
		//remove_call_out("do_lianyao");
		
		call_out("do_lianyao",2);
		
		me->improve_skill("zhiyao",(int)me->query_int(1)/2);
		
		//������ħ����
		if (!ob->query_temp("lianyao/xinmo"))
		{
			message_vision(HIR"$N����������ҩ������ҩ���ϳ�һ����ֵ�ҩζ�����Ϣ�����ɵ�һ��������!\n"NOR,me);
			ob->set_temp("lianyao/xinmo",1);
			if (me->query_skill("poison",1)<200)
				me->improve_skill("poison",(int)me->query_int(1)/2);

			call_out("qiangjie",6+random(5),me,1+random(3));
		}
		return 1;
	}
    else{
		//����������
		tell_object(me,HIR"\n\n\nҩ¯��һ��ζ���ҩ���Ȼ�������������ڣ�ҩ�����ˣ��Ͻ����ɣ�\n"NOR);
		ob->set_temp("lianyao/lianyaodone",1);
		ob->set_temp("lianyao/time",time());
		me->add_busy(2);
		return 1;
	}
	
}
//ʧ�ܱ��
int do_fail()
{
	object me,ob;
	object* inv;
	int i;
	ob=this_object();
	me=this_player();
	inv = deep_inventory(me);

	for (i=0;i>sizeof(inv);i++ )
	{
		destruct(inv[i]);
	}
	me->delete_temp("lianyao");
	ob->delete_temp("lianyao");
	ob->delete_temp("liquid");
	ob->delete("lianyao");

	tell_object(me,WHT"��ҩʧ�ܣ�ҩ¯��һƬ�������̱ǵ�ζ������,�ȳ�����!\n"NOR);
	me->apply_condition("flower_poison",2+random(3));
	return 1;
}
//��ҩ
int do_kanyao(string arg)
{
        object me=this_player();
        object yl=this_object();
        object* obs;
        object yc;
        int se,i,j;
        string msg,pre;
        string * day=({ "һ","��","��","��","��","��","��","��","��"});
        string * sc=({ "һ","��","��","��","��","��","��","��","��","ʮ","ʮһ"});

        if(arg)
        {
                if(!objectp(yc=present(arg, yl)))
                        return notify_fail("ҩ¯��û��"+arg+"���ֶ�����\n");
                if(!yc->query_temp("lianyao/bad"))
                {
                        se=yc->query("times")+uptime()-yc->query("stime");
                        if(se<=MAXS)
                        {
                                i=se/240;
                                se=se-i*240;
                                pre="("+yc->query("8type")+yc->query("5type")+"��)";
                                msg="�Ѿ�������";
                                if(i>0)
                                        msg=msg+day[i-1]+"��";
                                i=se/20;
                                if(i>0)
                                        msg=msg+sc[i-1]+"��ʱ����\n";
                                else if(msg=="�Ѿ�������")
                                        msg=msg+"һ��ʱ��������\n";
                                msg=pre+msg;
                        }
                        else
                        {
                                msg="��\n";
                                yc->set("name","�廵�˵�"+yc->query("name"));
                                yc->set_temp("lianyao/bad",1);
                                tell_object(me,yc->name(1)+msg);
                                destruct(yc);
                                add("yaocai",-1);
								return 1;
                        }
                }
                else
                        msg="��\n";
                tell_object(me,yc->name(1)+msg);
                return 1;
        }       
        obs=all_inventory(yl);
        for(j=0;j<sizeof(obs);j++)
        {
                yc=obs[j];
                if(!yc->query("lianyao/bad"))
                {
                        se=yc->query("times")+uptime()-yc->query("stime");
                        if(se<=MAXS)
                        {
                                i=se/240;
                                se=se-i*240;
                                pre="("+yc->query("8type")+yc->query("5type")+"��)";
                                msg="�Ѿ�������";
                                if(i>0)
                                        msg=msg+day[i-1]+"��";
                                i=se/20;
                                if(i>0)
                                        msg=msg+sc[i-1]+"��ʱ����\n";
                                else if(msg=="�Ѿ�������")
                                        msg=msg+"һ��ʱ��������\n";
                                msg=pre+msg;
                        }
                        else
                        {
                                msg="��\n";
                                yc->set("name","�廵�˵�"+yc->query("name"));
                                yc->set_temp("lianyao/bad",1);
                                tell_object(me,yc->name(1)+msg);
                                destruct(yc);
                                add("yaocai",-1);
                                continue;
                        }
                }
				else
                        msg="��\n";
                tell_object(me,yc->name(1)+msg);
        }
        return 1;
}
//Ϩ��
//ֻ����ʾ�ɹ���������������Ч����

int do_miehuo(string arg)
{
        object me, ob;
        object *inv;
		int i;
        me = this_object();
        ob = this_player();
        inv = deep_inventory(me);
		
        if (!arg||arg!="lu")
        {
			return notify_fail("��Ҫ��ʲô���\n");
        }
		if( ob->is_busy())
                return notify_fail("����æ���ء�\n");
        if( ob->is_fighting())
                return notify_fail("������ս����\n");
        if( !sizeof(inv))
                return notify_fail("¯������û�ж�����\n");
        if( me->query_temp("lianyao/open") )
                return notify_fail("¯���������أ�Ϲ��ʲô��\n");
        if( !me->query("lianyao/doing") && !me->query("lianyao/fired") )
                return notify_fail("¯�ӻ�û���\n");
        if( !me->query_temp("lianyao/lianyaodone") )
                return notify_fail("�����ڰ�ҩ�У���û����ҩ�أ�\n");

		if (time()-me->query_temp("lianyao/time")>15)
		{
			me->delete_temp("lianyao");
			ob->delete_temp("lianyao");
			ob->delete_temp("liquid");
			ob->delete("lianyao");
			me->delete("lianyao");
			for (i=0;i>=sizeof(inv);i++ )
			{
				destruct(inv[i]);
			}
			return notify_fail("�����̫���ˣ�ҩ¯�ڵ�ҩ�������ˣ�\n");
		}
		if (present("xinmo",environment(this_object())))
		{
			return notify_fail("����ħ��δ�����ϡ���Ϳ������\n");
		}
		//remove_call_out("do_drug");
        //remove_call_out("do_check");
        //remove_call_out("do_ready");
        //remove_call_out("do_confirm");
        //remove_call_out("do_failed");
        
		//call_out("do_drug", 3 , me);
		message_vision(RED"\n$N��ҩ¯�µĲ�𽥽���Ϩ���ˣ��ȴ�ҩ¯��ȴ������\n"NOR, ob);
		//me->delete("lianyao");
       // ob->delete("lianyao");
		me->set_temp("lianyao/miehuo",1);
		ob->set_temp("lianyao/miehuo",1);
		//me->delete("lianyao/fired");
		me->delete_temp("liquid");
		me->delete("lianyao");
        ob->add_busy(3);
        return 1;

}

//ȡҩ
int do_quyao(string arg)
{
        object me=this_player(),yl=this_object(),* obs,yao;
        mapping ycl=(["��":0,"��":0,"��":0,"ˮ":0,"ľ":0]);
        //mapping 8type=(["Ǭ":0,"��":0,"��":0,"��":0,"��":0,"��":0,"��":0,"��":0]);
        mapping yc=([]);
        string type5,type88,* order;
        string* num=({"0","1","2","3","4","5","6","7","8"});
        string* type=({"��","��","��","ˮ","ľ"});
        string* type8=({"Ǭ","��","��","��","��","��","��","��"});
        int i,se,j,sl,sllv,polv,sesx,add,total,k;
        string msg;
        mapping myfam;

        myfam = (mapping)me->query("family");
        if(!myfam || myfam["family_name"] != "������")
        {
           return notify_fail("�㲻�������̵��ӣ�ȡ����!\n");
        }
        sllv=me->query_skill("shenlong-yaoli",1);
        polv=me->query_skill("poison",1);
        sesx=(sllv+polv/2)*72/10;
        if(sllv<101 || polv<101)
                return notify_fail("�������ҩ��ѧ�Ͷ������˽⻹������������ҩ��\n");
        
		if(!yl->query_temp("lianyao"))
                return notify_fail("ҩ¯�ｹ��һƬ��ֻʣ��һ�Ѻ�ɫҩ�ۣ�\n");
        //��ħ����
		//if(me->query_temp("lianyao/rumo"))
          //      return notify_fail("���ȿ˷�����ħ��˵��\n");

		if (!yl->query_temp("lianyao/miehuo"))
        {
			return notify_fail("����δ���㲻�����֣�\n");
        }
		if (!yl->query("lianyao/open"))
        {
			return notify_fail("ҩ¯��δ�򿪣������ȡҩ��\n");
        }

		obs=all_inventory(yl);
        
		if(sizeof(obs)==0)
                return notify_fail("ҩ¯��û�ж�����\n");
        msg=me->query("id");
        for(i=0;i<sizeof(obs);i++)
{
                if(obs[i]->query("id")!="yao cao")
                        continue;
                se=obs[i]->query("times")+uptime()-obs[i]->query("stime");
                if(se>MAXS)
                {
                        obs[i]->set("name","�廵�˵�"+obs[i]->query("name"));
                        obs[i]->set("lianyao/bad",1);
                        destruct(obs[i]);
                        add("yaocai",-1);
                        continue;
                }
                if(se>sesx)
                        se=sesx;
                type5=obs[i]->query("5type");
                type88=obs[i]->query("8type");
                msg=sprintf("%s %s%s:%d",msg,type5,type88,se);
                if(sizeof(yc)==0)
                {
                        yc=([ type5:([type88:([num[i]:se])])]);
                }
                else
                {
                        if( undefinedp(yc[type5]) )
                        {
                                yc[type5]=([type88:([num[i]:se])]);
                        }
                        else if( undefinedp(yc[type5][type88]))
                        {
                                yc[type5][type88]=([num[i]:se]);
                        }
                        else
                        {
                                yc[type5][type88][num[i]]=se;
                        }       
                }
                destruct(obs[i]);
                add("yaocai",-1);
        }
        add=0;
		for(i=0;i<5;i++)
        {
                if( undefinedp(yc[type[i]]))
                        continue;
                else if(sizeof(yc[type[i]])>=8)
                {
                        sl=10000;
                        for(j=0;j<8;j++)
                        {
                                if( undefinedp(yc[type[i]][type8[j]]))
                                        continue;
                                order=keys(yc[type[i]][type8[j]]);
                                if(yc[type[i]][type8[j]][order[0]]<sl)
                                        sl=yc[type[i]][type8[j]][order[0]];
                                map_delete(yc[type[i]][type8[j]],order[0]);
                                if(sizeof(yc[type[i]][type8[j]])==0)
                                        map_delete(yc[type[i]],type8[j]);
                        }
                        ycl[type[i]]=sl*64;
                }
                else
                {
                        for(k=0;k<2;k++)
                        {
                                while(1)
                                {
                                        for(j=k;j<8;j++,j++)
                                        {
                                                if(undefinedp(yc[type[i]][type8[j]]))
                                                        break;
                                        }
                                        if(j>=8)
                                        {
                                                sl=10000;
                                                for(j=k;j<8;j++,j++)
                                                {
                                                        if( undefinedp(yc[type[i]][type8[j]]))
                                                                continue;
														order=keys(yc[type[i]][type8[j]]);
                                                        if(yc[type[i]][type8[j]][order[0]]<sl)
                                                                sl=yc[type[i]][type8[j]][order[0]];
                                                        map_delete(yc[type[i]][type8[j]],order[0]);
                                                        if(sizeof(yc[type[i]][type8[j]])==0)
                                                                map_delete(yc[type[i]],type8[j]);
                                                }
                                                ycl[type[i]]=ycl[type[i]]+sl*16;
                                        }
                                        else
                                                break;
                                }
                        }
                        for(k=0;k<4;k++)
                        {
                                while(1)
                                {
                                        for(j=k*2;j<k*2+2;j++)
                                        {
                                                if(undefinedp(yc[type[i]][type8[j]]))
                                                        break;
                                        }
                                        if(j>=k*2+2)
                                        {
                                                sl=10000;
                                                for(j=k*2;j<k*2+2;j++)
                                                {
                                                        if( undefinedp(yc[type[i]][type8[j]]))
                                                                continue;
                                                        order=keys(yc[type[i]][type8[j]]);
                                                        if(yc[type[i]][type8[j]][order[0]]<sl)
                                                                sl=yc[type[i]][type8[j]][order[0]];
                                                        map_delete(yc[type[i]][type8[j]],order[0]);
                                                        if(sizeof(yc[type[i]][type8[j]])==0)
                                                                map_delete(yc[type[i]],type8[j]);
                                                }
                                                ycl[type[i]]=ycl[type[i]]+sl*4;
                                        }
                                        else
                                                break;
}
                        }
                }
                for(j=0;j<8;j++)
                {
                        if( undefinedp(yc[type[i]][type8[j]]))
                                        continue;
						order=keys(yc[type[i]][type8[j]]);
                        for(k=0;k<sizeof(order);k++)
                        {
                                ycl[type[i]]=ycl[type[i]]+yc[type[i]][type8[j]][order[k]];
                                map_delete(yc[type[i]][type8[j]],order[k]);
                        }
                        map_delete(yc[type[i]],type8[j]);
                }
                add+=ycl[type[i]];
        }
        total=add;
        add/=200;
        if(add>100)
                add=100;
        me->improve_skill("shenlong-yaoli",add,0);
        me->improve_skill("poison",add,0);
       //������ҩ��
		me->improve_skill("zhiyao",add,0);

        yao=new("/d/sld/npc/obj/yaowan");
        if(!objectp(yao))
                return notify_fail("��ϧ�����ҩ���廵�ˡ�\n");
        msg=msg+" "+file_name(yao);
        j=0;k=0;
        yao->set("types",0);
        for(i=0;i<5;i++)
        {
                if(ycl[type[i]]<total*1/20)
                        continue;
                yao->add("types",1);
                if(type[i]=="��")
                {
                        yao->set(type[i],ycl[type[i]]/100);
                        msg=sprintf("%s %s:%d",msg,type[i],ycl[type[i]]/100);
                }
                else
{
                        yao->set(type[i],ycl[type[i]]/10);
                        msg=sprintf("%s %s:%d",msg,type[i],ycl[type[i]]/10);
                }
                if(ycl[type[i]]>=total*7/10)
                        k=i+1;
                else if((ycl[type[i]]>=total*19/100) && (ycl[type[i]]<=total*21/100))
                        j++;
        }
        if(k>0)
        {
                yao->set("poison",type[k-1]);
                yao->set("zycs",ycl[type[k-1]]/1000);
                msg=sprintf("%s %s::%d",msg,type[k-1],ycl[type[k-1]]/1000);
        }
        else if(j==5)
        {
                yao->set("poison","ȫ");
                yao->set("zycs",total/1000);
                msg=sprintf("%s ȫ::%d",msg,total/1000);        
        }
        msg=msg+"��\n";
//	write_file("/u/emnil/makeyao",msg);
        write("���������ҩ���ʲôӢ�����֣�(ȱʡ��danyao)");
		yao->move(me);
        input_to("yao_id",0,yao);
        return 1;
}

void yao_id(string arg,object yao)
{
        if(arg && arg!="")
                yao->set("id",arg);
        else
                yao->set("id","danyao");
		this_player()->set_temp("lianyao/yaoid",arg);

        write("���������ҩ���ʲô�������֣�(ȱʡ����ҩ)");
        input_to("yao_name",0,yao);
}

void yao_name(string arg,object yao)
{
        yao->set_name(HIG "��ҩ" NOR, ({yao->query("id"),"yao","dan"}));
		if(arg && arg!="")
        yao->set("name",arg);
		this_player()->set_temp("lianyao/yaoname",arg);

        write("���������������ҩ��(ȱʡ������һ�������̶������Ƶĵ�ҩ��)");
        input_to("yao_long",0,yao);
}

void yao_long(string arg,object yao)
{
    int i,add,qnadd;
	object ob;
    object me=this_player();
	ob=this_object();

	if(arg && arg!="")
		yao->set("long",arg+"\n");
        message_vision(HIY+"\n$N"+HIY+"���ڴ���ħ����������ҩ¯���ó���һ��ҩ���ӡ�\n"NOR,me);
        yao->set("owner",me->query("id"));
		this_player()->set_temp("lianyao/yaolong",arg);

		if(!yao->move(me))
                yao->move(environment(me));
		ob->delete_temp("lianyao");
		ob->delete("lianyao");

       /* 
		if((add=me->query("mkyexp"))!=0)
        {
                i=me->query("max_pot")-me->query("potential");
                qnadd=add/2;
                if ( i<qnadd) qnadd = i;
                
                me->add("combat_exp",add);
                me->add("potential",qnadd);
                me->add("shen",-add*2);
                me->delete("mkyexp");

                tell_object(me,"��սʤ��ħ�������"+add+"�㾭�飬"+qnadd+"��Ǳ�ܣ�"+add*2+"�㸺��\n");
        }*/
}
