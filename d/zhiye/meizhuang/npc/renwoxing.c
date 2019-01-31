// ren.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int ask_bijian();
int ask_ronggong();
int ask_dongfang();
int ask_xxdf();
int ask_ruozhuo();
int ask_qianbian();
void create()
{
	set_name("������", ({ "ren woxing", "ren","woxing" }));
	set("nickname",HIR"ħ�̽���"NOR);
	set("long", "ֻ����һ�ų��������ף���ɫѩ�ף����ް��Ѫɫ��üĿ���㣬
������ߣ�һͷ�ڷ���������һϮ������\n");
	set("gender", "����");
	set("age", 55);
	set("attitude", "friendly");
	set("shen_type", -1);
	set("no_get", 1);
	set("str", 30);
	set("per", 27);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 40000);
	set("max_jing", 10000);
	set("eff_jingli",10000);
	set("neili", 80000);
	set("max_neili", 40000);
 	set("jiali", 200);
	set("combat_exp",12000000);
	set("score", 500000);
    set("xixing",2);
	//set("quest/");

	set_skill("literate", 200);         // ����ʶ��
	set_skill("force",500);            // �����ڹ�
	set_skill("strike",500);           // ����ָ��
	set_skill("dodge",500);            // ��������
	set_skill("parry",500);            // �����м�
	//set_skill("dagger",400);           // �����̷�
	set_skill("sword",500);            // ��������
	set_skill("blade",500);
	set_skill("club",500);
	set_skill("poison",180);
	set_skill("throwing",500);
	set_skill("huanmo-wubu",500);  // �����
	set_skill("tianmo-gun",500);  // ��ħ������
	set_skill("qixian-wuxingjian",500);// �������ν�
	set_skill("xixing-dafa",500);      // �����ķ�
	//set_skill("wudang-quan",400);        // ̫�泤ȭ
	set_skill("damo-jian",500);        // ��Ħ����
	set_skill("taiji-jian",500);       // ̫������
	set_skill("huifeng-jian",500);     // �ط������
	set_skill("taishan-jianfa",500);    // ̩ɽ����
	set_skill("hengshan-jianfa",500);    // ��ɽ����
	set_skill("mantian-huayu",500);   // 
	set_skill("huashan-jianfa",500);    // ��ɽ����
	set_skill("songshan-jian",500);   // ��ɽ����
	set_skill("tianmo-jian",500);
	set_skill("tianmo-zhang",500);
	//set_skill("tianmo-shou",400);
	set_skill("tianmo-dao",500);
	set_skill("tianmo-gun",500);
	set_skill("tianmo-jue",200);

	map_skill("force", "xixing-dafa");
	map_skill("blade", "tianmo-dao");
	map_skill("club", "tianmo-gun");
	map_skill("sword", "qixian-wuxingjian");
	map_skill("strike", "tianmo-zhang");
	map_skill("dodge", "huanmo-wubu");
	map_skill("parry", "qixian-wuxingjian");
	prepare_skill("strike", "tianmo-zhang");
	set("quest/xixing/pass",2);
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
                (: perform_action, "sword.qianbian" :),
                (: perform_action, "sword.pomo" :),
                (: exert_function, "xixing" :),
	}));

    set("inquiry", ([
                "�Ƚ�" :  (: ask_bijian :),
                "����" :  (: ask_bijian :),
                "��ľ��" : "Ҫ�ú�ľ��Ϸ����ȿ�����Ľ�����\n",
	        	"�������" : "���������������̣��͵����Ĵ��ó��ϡ�",
		        "���Ǵ��ڹ�"     :  (: ask_ronggong :),
                "��������"     : (: ask_dongfang :),
			    "���Ǵ��ر�"     : (: ask_xxdf :),
			    "ǧ���򻯾���"     : (: ask_qianbian :),
			    "��ħ�ƾ���"     : (: ask_ruozhuo :),
	]) );

	create_family("�������", 5, "����");
 	setup();
	carry_object("/clone/armor/changpao")->wear();
	carry_object("/clone/weapon/sword")->wield();
}

int ask_bijian()
{
	object weapon, me = this_player(), ob = this_object();

        if (!objectp(weapon = ob->query_temp("weapon")))
	{
		weapon = new("/clone/weapon/sword");
		weapon -> move(ob);
		command("wield sword");
	}
	if(me->query("combat_exp")<5000000)
	{
		message_vision("$N����˵���������������Ұݼ�����ǰ�����������ָ�̡���\n$n��Ц����������㾭��Ҹ��ұȽ�������5m����˵����\n", me, ob );
		message_vision("$n��$N���֮�ʣ�һ�Ž�$N�߳��˼�������\n", me, ob );
		me->move("d/hz/baidi");
		return 1;
	}
	if(!me->query_temp("quest/xxdf/start"))
	{
		message_vision("$N����˵���������������Ұݼ�����ǰ�����������ָ�̡���\n$n��Ц�����������Ĺ���ô���ҽ������ң�����\n", me, ob );
		return 1;
	}
	else {
	message_vision("$N����˵���������������Ұݼ�����ǰ�����������ָ�̡���\n$nЦ���������ÿ������������Ҽ�į���ɶ�л��������\n", me, ob );
	message_vision("$N���������ҡ���\n$n���˵�ͷ��˵��������ֻ��������Ľ�����������Ĺ��У���˵����Ҳδ����ʤ�����㡣��\n\n", me, ob);
    command("Ц�����������ӽ������µ�һ�����ұȽ���������\n");
	command("enable sword damo-jian");
	say(HIR"\n�����д��һ�����������ɴ�Ħ����"NOR"��"HIR"��Ħ������"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n��һ�С�\n");
	command("enable sword taiji-jian");
	say(HIR"\n�����д��һ�������䵱̫������"NOR"��"HIG"��������"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�ڶ��С�\n");
	command("enable sword huifeng-jian");
	say(HIR"\n�����д��һ�����������ɻط������"NOR"��"HIW"��ԭ�ٻ�"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�����С�\n");
	command("enable sword songshan-jianfa");
	say(HIR"\n�����д��һ��������ɽ����ɽ����"NOR"��"HIM"��������"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�����С�\n");
	command("enable sword taishan-jianfa");
	say(HIR"\n�����д��һ������̩ɽ��̩ɽ����"NOR"��"HIY"������"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�����С�\n");
	command("enable sword huashan-jianfa");
	say(HIR"\n�����д��һ��������ɽ�ɻ�ɽ����"NOR"��"MAG"�����������ɽ�"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�����С�\n");
	command("enable sword hengshan-jianfa");
	say(HIR"\n�����д��һ��������ɽ�ɺ�ɽ����"NOR"��"CYN"��ɽ����ط�ʮ��ʽ"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
		say("\n�����С�\n");
	command("enable sword hengshan-jianfa");
	
	say(HIR"\n�����д��һ��������ɽ�ɺ�ɽ����"NOR"��"WHT"�������"NOR"������\n"NOR);
	COMBAT_D->do_attack(ob, me, query_temp("weapon"));
	if(present(me, environment()))
	{
    say(HBMAG"\nͻȻ�����з���һ���޺���Ķ���һ�����飬һ����ע�⡣��������\n\n"NOR);
	say("\n������̾�˿�����˵����������û�����С���\n");
	me->set_temp("renwoxing/bijian", 1);
	me->set("qi",-1);
	me->delete_temp("quest/xxdf/start");
	me->set_temp("quest/xxdf/startlass",1);
		return 1;
	         }
          }
         }
        }
       }
      }
     }
   }
  }
	return 1;
}

void attempt_apprentice(object ob)
{
	mapping fam;
    if ((int)ob->query("quest/xxdf/pass",1) < 1)
	{
		command("say ���ǲ�������ͽ�ġ�");
		return;
	}
    if (!(fam = this_player()->query("family")) || fam["family_name"] !="�������"){
             command("thank "+ (string)ob->query("id"));
             command("say ���뱾�������������Ҳ�������Ϊͽ�ģ�");
             return 0;
        }
    if ((int)ob->query_skill("xixing-dafa",1) < 450)
	{
		command("say �����Ǵ��ϣ�" + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö��µ㹦��");
		return;
	}
   
	    command("say �ðɣ���Ȼ�������ͶԵ���Ϸ���������ˡ�");
        command("�Ϸ��յ������ͽ����������С����ı�Ӧ����!");
	    command("recruit " + ob->query("id"));
	    message_vision(
HIG"\n$N�������ŵ�����������������һ��Ӣ���˵ã��ο��������֮�к͸�"+
"��ͬ�ֻࣿ�����������Ϊͽ�������Գ���ɽ���Ե�����������������"+
"��������һ���Ƚ�������ĺ���ʤ�ţ������������ֻ��������գ����"+
"��ض�ô����������ү�ӳ��ú��Σ������µ���Ů���ף���Ҫɱ��һ��"+
"��ɱ��һ�������˸�����ү��Υ������ʹ��֮������\n"NOR, ob);
ob->set("title",HIR"��������������״�����"NOR);
  
}
//���β���ѧ���书
int prevent_learn(object ob, string skill)
{
	if (skill == "tianmo-jian"
	    ||skill == "taiji-jian"
		||skill == "huifeng-jian"
		||skill == "tanshan-jianfa"
		||skill == "hengshan-jianfa"
		||skill == "songshan-jian"
		||skill == "huashan-jianfa"
		||skill == "poison"
	    ||skill =="damo-jian")
		return 1;
	return 0;
}
int ask_ronggong() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й����Ǵ��ڹ��������������\n"NOR, me, this_object());
	if(!me->query_temp("xixing/killeddf"))
	{
		command("?");
		command("say �㲻ɱ�˶�����������ô����������ʲô��"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/xxdf/pass")==2)
	{
		command("?");
		command("say �㿪ʼ������ˣ������⿪�ˣ���������ʲô��"NOR);
		me->set("title",HIC"�������"HIB"���Ǵ󷨴���"NOR);
		me->set("mytitle/quest/xxdftitle",HIC"�������"HIB"���Ǵ󷨴���"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(!me->query("quest/xxdf/pass"))
	{
		command("?");
		command("say �������Ǵ���ʲô��������֪����������̸�ںϣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	
	if(me->query("quest/xixing/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/xixing/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵�������ɣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("xixing-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ���Ǵ󷨻�û��ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("quest/xixing/time",time());
	me->set("quest/xixing/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say ���Ǵ����������߾�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
	tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬�����Ǵ󷨳����ںϵ����������ƺ���Щ�ĵá�\n"NOR);
	tell_object(me,HIW"\n�㰴�������е��й�·�ߣ���ʼ���������ɵĸ��ֹ��������ڹ�����ͼ�����ںϡ�\n"NOR);
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	me->delete_temp("xixing/killeddf");
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	if(i<3&&random(me->query("kar"))>28)
	{
		tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬���ﳣ����䣬������ȣ�����������ȿ���ˮ��������Ϣ��\n"+
			"ɢ֮��������Ѩ~����������ɢ֮�����������пգ��ƹȺ���~������Ϣ��ɢ����֫������֮������ע������\n"NOR);
		tell_object(me,HIW"\nֻ�����Ե���������ţ�����ͥ���ۼ������У�Ȼ��ɢ����֫�����ϵ������ƺ����˺ܶࡣ\n"NOR);
		tell_object(me,HIC"\n��һ�ε�ɢ������ǰ��������������ԵĲ�ͬ����ǰɢ���ֻؾۼ��ڵ������ε�ɢ��ȴ����ɢ����\n"NOR);        
		tell_object(me,MAG"\n����û����쳣�����ů��������綬��ů�����Դ�Ϊʼ��ѭ���������㳹�����������Ǵ󷨵��ڹ���\n"NOR);
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/xxdf/pass",2);
		me->set("title",HIC"�������"HIB"���Ǵ󷨴���"NOR);
		me->set("mytitle/quest/xxdftitle",HIC"�������"HIB"���Ǵ󷨴���"NOR);
		log_file("quest/xxdfrg", sprintf("%8s(%8s) ʧ��%d�κ󣬳����������Ǵ󷨵��ںϡ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/xixing/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/xixing/fail",1);
		command("buddha");
		tell_object(me,HIR"�����˽��������е�ָ��,�������У�����һ��ʹ���㻥���ͻ�������羭���һ�����ܲ�ס���۵��³�һ����Ѫ��\n"NOR);
		tell_object(me,HIY"��һ�ε����У��ķ����㼫��ľ���������������û�����ڻ��ͨ����ſ���Ķ�������û��һ˿������\n"NOR);
		me->unconcious();
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/xxdfrg", sprintf("%8s(%8s) ���Ǵ��ڹ���������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/xixing/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}

int ask_dongfang() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	//message_vision(HIC"$N��$n����й����Ǵ��ڹ��������������\n"NOR, me, this_object());
	
	if(!me->query("quest/xxdf/pass")||me->query("family/family_name")!="�������")
	{
		command("?");
		command("say �������Ǵ���ʲô��������֪��������ɱ����������������ǣ�"NOR);
		command("kick "+me->query("id"));
		return 1;
	}

	if(me->query_skill("xixing-dafa",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ���Ǵ󷨻�û��ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	command("say �ߣ�����������Ȼ��ȡ���ҵĽ���֮λ������ȴ�����������������������������˵�һ�ˡ�");
	tell_object(me,HIY"\n����ϰ�����Ǵ󷨵��ڹ�������ø��ҰѶ������ܸ���ɱ�ˣ����򣬱����↪�¡�\n"NOR);
	me->set_temp("xinxing/askren",1);
	return 1;
}
int ask_xxdf() 
{
	object me = this_player();
	object ob;
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$Nһ�����ģ������ջ��������ţ���$n����й����Ǵ��ر���������⡣\n"NOR, me, this_object());
	if (present("xixing miji",me))
	{
		command("?");
		command("say �����ϲ�����һ��ô���������������"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if(!me->query("quest/xxdf/pass"))
	{
		command("?");
		command("say �������Ǵ���ʲô��������֪�����������������"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
    ob = new("/d/meizhuang/obj/xixing-book");
    ob->move(me);   
	
	command("say �ߣ��ڵ����ﲻ���������Ǵ󷨵��ؼ�ô�����ﲻ�ú�ѧϰ����ʲô���������ĵģ�С���ҿ�����");
	tell_object(me,HIY"\n�����дӻ�������һ���ؼ��ر���������Ļ��\n"NOR);
	//me->set_temp("xinxing/askren",1);
	return 1;
}

//��ħ�ƾ���
int ask_ruozhuo() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й���ħ���С���׾ʵ�ɡ��������������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="�������")
	//||me->query("family/master_id")!="ren woxing"
	{
		command("?");
		command("say �㲻���ҵ��ӣ���������ʲô��"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hmy/tmzf/ruozhuo/pass"))
	{
		command("?");
		command("say ���Ѿ���������׾ʵ�ɵĵ�����������ʲô��"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	
	if(me->query("quest/hmy/tmzf/ruozhuo/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/hmy/tmzf/ruozhuo/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵��������ˣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("tianmo-zhang",1)<450||me->query_skill("strike",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�Ʒ���û��ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("quest/hmy/tmzf/ruozhuo/time",time());
	//me->set("tmzf/combat_exp",me->query("combat_exp")); 
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	command("heng "+me->query("id"));
	command("say ��ħ����׾ʵ����������Ʒ���߾�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
	tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬����ħ����׾ʵ�ɵİ��忪ʼ˼����������Ȼ�������Ͷ�롣\n"NOR);
	
	command("whisper "+me->query("id")+" �����ǿ죬���������������ת�����һ�ģ���ж��䡣\n");
	command("smile "+me->query("id"));
	
	if(i<5 
		&& random(me->query("kar"))>=25
		&&me->query("kar")<31)
	{
		tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬������ת��Ϣ������ʱ��ʱ������ò��������Ʊ�׾������ʵ������֮����\n"+
			"������ʵ�޻������Ʊ�׾ȴ�����мܡ��������Ի���������ʹ�������ڽ�����\n"NOR);
		
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/hmy/tmzf/ruozhuo/pass",1);
		log_file("quest/tmzf", sprintf("%8s(%8s) ʧ��%d�κ�������׾ʵ�ɵİ��ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/hmy/tmzf/ruozhuo/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hmy/tmzf/ruozhuo/fail",1);
		command("heng ");
		command("kick "+me->query("id"));
		tell_object(me,HIR"����Ȼ�����������е�ָ��,�����������˸��ְ��ء�\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/tmzf", sprintf("%8s(%8s) ��ħ����׾ʵ�ɾ�������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/hmy/tmzf/ruozhuo/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}
//�������ν�����--ǧ����

int ask_qianbian() 
{
	object me = this_player();
	int i,j;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N��$n����й��������ν��С�ǧ���򻯡��������������\n"NOR, me, this_object());
	if(me->query("family/family_name")!="�������"||me->query("family/master_id")!="ren woxing")
	{
		command("?");
		command("say �㲻���ҵ��ӣ���������ʲô��"NOR);

		command("kick "+me->query("id"));
		return 1;
	}
	if(me->query("quest/hmy/qxwxj/qianbian/pass"))
	{
		command("?");
		command("say ���Ѿ�������ǧ���򻯵ĵ�����������ʲô��"NOR);
		command("kick "+me->query("id"));		
		me->set("mytitle/quest/qbwhtitle",HIC"ǧ����"HIB"��䲻������"NOR);
		return 1;
	}
	command("look "+me->query("id"));	
	//��ͨ�������
	
	if(me->query("quest/hmy/qxwxj/qianbian/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say �Ѿ���δ��ڣ�����ô����û������,�湻���ģ�");
		command("puke "+me->query("id"));
		return 1;
	}
	//�书ѧϰ֮����Ҫ���һ�죬������Ҫ���50K
	if( time()-me->query("quest/hmy/qxwxj/qianbian/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say �����Ƚ̵��������ˣ�����ɡ�");
		return 1;
	}
	if(me->query_skill("qixian-wuxingjian",1)<450||me->query_skill("sword",1)<450)
	{
		command("look "+me->query("id"));
		command("say ���㵱ǰ�������ν���û��ɣ����»����������򣬻���ץ��ȥ����ȥ�ɡ�");
		return 1;
	}
    
	me->set("quest/hmy/qxwxj/qianbian/time",time());
	//me->set("tmzf/combat_exp",me->query("combat_exp")); 
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	command("heng "+me->query("id"));
	command("say �������ν�ʵ��������̽�����߾�������Ȼ����������Ҿ�˵����������������û����������ˡ�");
	tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬���������ν�ǧ���򻯵İ��忪ʼ˼����������Ȼ�������Ͷ�롣\n"NOR);
	
	command("whisper "+me->query("id")+" �����ǿ죬���������������ת�����һ�ģ���ж��䡣\n");
	command("smile "+me->query("id"));
	
	if(i<3 && random(me->query("kar"))>=28&&me->query("kar")<31)
	{
		tell_object(me,HIY"\n�㰴�ս��������е�ָ�㣬������ת��Ϣ������ʱ��ʱ������ò��������Ʊ�׾������ʵ������֮����\n"NOR);
		
		command("look "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/hmy/qxwxj/qianbian/pass",1);
		me->set("title",HIC"ǧ����"HIB"��䲻������"NOR);
		me->set("mytitle/quest/qbwhtitle",HIC"ǧ����"HIB"��䲻������"NOR);
		log_file("quest/qxwxjqianbian", sprintf("%8s(%8s) ʧ��%d�κ������������ν�ǧ���򻯵İ��ء�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/hmy/qxwxj/qianbian/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("quest/hmy/qxwxj/qianbian/fail",1);
		command("heng ");
		command("kick "+me->query("id"));
		tell_object(me,HIR"����Ȼ�����������е�ָ��,�����������˸��ְ��ء�\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/qxwxjqianbian", sprintf("%8s(%8s) ǧ���򻯾�������ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/hmy/qxwxj/qianbian/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}