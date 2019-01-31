// Room: /d/huashan/cave.c
// Date: Look 99/03/25
// Update by lsxk@hsbbs 2007/8/8  add huashan perform fengyi quest

#include <ansi.h>
string look_dazi();
inherit ROOM;
#include "fengyi5.h"
void create()
{
        set("short", "�ܶ�");
        set("long",@long
���߽���������ʯ�ں��棬���ж��죬�Ǹ����ݵ�ǧ��֮�ڵĴ󶴣�����
���߾ߺ��ǣ����������ԣ����Ծ��б��С�ɽ���ı��������ͻ��һ���ʯ��
����һ��ƽ̨����ʯ֮�¿���ʮ��������(dazi)��������Ѹ���ʯ�����տ�
ʱ��ֻ��һ���̵ֿ����ų˷��ų����ƻ�ɽ�����ڴˡ���һ��֮�Ե�ʯǽ(wall)
�Ͽ����������Σ���Ȼ��ʹ���ӵ��������ƽ�ʹ�����εĽ�������Щ����֮�ԣ�
��Ȼ����һ���ּ�(ziji)���㲻���뿴(kan)���д��Щʲô��
long);
        set("exits", ([
                "out" : __DIR__"rukou",
			    "east" : __DIR__"cave1",
        ]));
	set("item_desc", ([
            	"dazi" :  (:look_dazi:),
            	"wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L


TEXT
        ]));
        //set("no_fight", 1);
        setup();
}

void init()
{
    object me=this_player();
	if ((me->query("family/family_name")=="��ɽ��" 
		||me->query("family/family_name")=="��ɽ��"
	    ||me->query("family/family_name")=="�������")
		&& me->query_temp("hssb/juejiasked"))
	{
	    message_vision(HIC"$N�ս���ɽ���������������ƺ��м�����Ӱ�ζ���������ɽʯ�ڵ���Ϣ�Ѿ�й©�ˡ�\n"NOR,me);
	    message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ����ֻ�ɽʯ���ڵ����ܣ�\n"NOR, users());
		//me->delete_temp("hssb/juejiasked");
		//me->set_temp("hssb");
	}
	//����4û���Ƚ�fy4
	if(this_player()->query("quest/hsjf/fengyi4_fail")){
        add_action("do_yanjiu", "yanjiu");
        this_player()->set_temp("quest/huashan/fengyi_yanjiu",1);
    }
	//����4��û��5�����һ�죬û��ɱ��killer
    if(this_player()->query("quest/hsjf/fengyi4")=="pass"
      &&this_player()->query("quest/hsjf/fengyi5")!="pass"
     // &&(int)this_player()->query("quest/hsjf/fengyi5_fail")<5
      && time()-(int)this_player()->query("quest/hsjf/fengyi4_time")>86400
      &&this_player()->query("quest/huashan")=="����"
      &&!this_player()->query("quest/hsjf/fy5/kill_killer_pass")
      &&(!this_player()->query("quest/hsjf/fy5")||this_player()->query("quest/hsjf/fy5/yanlian")!="pass"))
     {
            this_player()->set_temp("fengyi5_zhuomo",1);
            call_out("fengyi5_init",3+random(4),this_player());
     }

    add_action("do_kan", "kan");

    if(this_player()->query("quest/hsjf/fy5/chuaimo")
       &&this_player()->query("quest/hsjf/fy5/kill_killer_pass")
       &&this_player()->query("quest/hsjf/fy5/yanlian")=="pass")
        add_action("do_chuaimo", "chuaimo");
}
//��Ħ���Ƿ���5
//��Ħ����
int do_chuaimo(string arg)
{
    int i,j;
	object me = this_player();
    if (me->query("family/family_name")!="��ɽ��"||me->query("quest/huashan")!="����")
        return notify_fail("��Ѿ���˼���������ǻ�ɽ���ں��ĵ��Ӷ��޷������⻪ɽ������\n");
    if(!arg)
        return notify_fail("��Ҫ��Ħʲô��\n");

    if(arg!="�з�����" && arg!="����")
        return notify_fail("��Ҫ��Ħʲô��\n");
	
	if ((time()-me->quest("quest/hsjf/fengyi5_time"))>86400) return notify_fail("������̫Ƶ���ˣ�\n");
	
	if  (me->query("quest/hsjf/fengyi5")) return notify_fail("���Ѿ��⿪���⣬����Ħʲô��\n");
	
    if(me->query("rigister")<3 &&(int)me->query("quest/hsjf/fengyi5_fail")>=5)
	{
        me->delete("quest/hsjf/fy5");
        return notify_fail(HIR"�������ʯ���ϵĽ��У���Ħ����Ħȥ�������޷�Ū����������Ⱳ��ҪŪ������ƺ��е㳬�����������Χ�ˡ�����\n"NOR);
    }
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);
	me->set("quest/hsjf/fengyi5_time",time());//��ʱ����
	if (me->query("kar")>25 && i<3)
	{
	
        write(HIG"�������ʯ���ϵĽ��У�������ղ����������ʹ�õ�������ͻȻ�������\n"+
                 "�⡰�з����ǡ������һ�У��㲻��������Ц����������~��ԭ����˰�!��\n"NOR);

        me->set("quest/hsjf/fengyi5","pass");
		//���ӻ�ɽʯ�ڵı��
		me->set("quest/hs/hssb/pass",1);
        me->delete("quest/hsjf/fy5");
        log_file("quest/fengyi5", sprintf(HIG"fy5�ɹ�!�з�����5Quest��¼��%s(%s)�ڻ�ɽ�ض�ʧ��%d�κ�"HIW"��Ħ"HIG"�ɹ�������%d��\n"NOR, me->name(1),me->query("id"), me->query("quest/hsjf/fengyi5_fail"), me->query("combat_exp")) );
        return 1;
    }
    write(HIY"�������ʯ���ϵĽ��У�������Ħ�ղ�������˵Ľ��У���Ȼ�����е�˼·���������޷����͸����\n"NOR);
    me->add("quest/hsjf/fengyi5_fail",1);	
    log_file("quest/fengyi5", sprintf(HIR"fy5ʧ�ܣ��з�����5Quest��¼��%s(%s)�ڻ�ɽ�ض�"HIW"��Ħ"HIR"ʧ��%d�Ρ�����%d��\n"NOR, me->name(1),me->query("id"),me->query("quest/hsjf/fengyi5_fail"), me->query("combat_exp")) );

    return 1;
}


int fengyi5_init(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave")
         return 1;

        write(HIY"��ʵ����Σ�������ּ�������ʯ��֮�����̵ġ�"HIC"�з�����"HIY"�����ƽ�\n"+
              "�������������������Ĳ����ƽ�һ�������������Ǳ��ŵ����С�"HIC"��\n"+
              "������"HIY"����\n"+
            HIR"\n��ֻ�������С�"HIC"�з�����"HIR"���������������ƺ������ϳ˵ĺ��н�����\n"+
              "���㲻����ʼ������ĥ����......\n\n"NOR);
        add_action("do_zhuomo","zhuomo");
        add_action("do_zhuomo","��ĥ");
    return 1;
}

int do_zhuomo(string arg)
{

    object me = this_player();

    if(!me->query_temp("fengyi5_zhuomo"))
        return notify_fail("��Ϲ��ĥɶ�أ��ø�ɶ��ɶȥ��\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    if(!arg) return notify_fail("��Ҫ��ĥʲô��\n");

    if(arg!="�з�����")
        return notify_fail("��Ϲ��ĥɶ�أ�\n");

    if((int)me->query_skill("huashan-jianfa",1)<350)
        return notify_fail("��Ļ�ɽ����ʵ��̫��,Ϲ��ĥ�˰��컹�Ƿ�����!\n");

    if(me->query("quest/hsjf/fengyi5")=="pass")
        return notify_fail("��ô�ţ������Դ������У�\n"NOR);

    if((int)me->query("quest/hsjf/fengyi5_fail")>=5 && me->query("registered")<3)
        return notify_fail("���ѽʾ���֭,����Ȼδ��,ֻ���½�����Ҳ�޷���͸�����а����ˣ�\n"NOR);

    fengyi5_zhuomo(me);

    return 1;
}
//������
string look_dazi()
{

       return "ÿ�ĸ���һ�ţ�һ�����ţ�ÿ���ֶ��г������������ɽʯ��\n"
              "���ü������ı��п��룬������硣ʮ������������䣬���н�������̬֮��\n"

        "\n"
          "      ����������������������������������\n"
          "      ����������������������������������\n"
          "      �����������塡���������ɡ���������\n"
          "      �����������ޡ��ܡ��¡�������������\n"
          "      �����������ȡ��䡡����ʤ����������\n"
          "      ���������������㡡�����ˡ���������\n"
          "      ����������������������������������\n"
          "      ����������������������������������\n"
          "      ����������������������������������\n";
}

int do_kan(string arg)
{
    object me = this_player();

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    if (!arg || (arg != "ziji" && arg != "�ּ�") )
		return notify_fail("���뿴ʲô��\n");

      switch (me->query("family/family_name"))
      {
        case "�������":
         if(me->query("quest/hmy/dlsmf/jueji")=="pass"||me->query_skill("dali-shenmofu",1)>1)
          return notify_fail("�㿴��ǽ�ϵĹ�����ʽ������Ͷ�룬������������ӿ�������ǹ���������£�\n");  
         if(me->query("quest/hmy/tmgf/jueji")=="pass")
          return notify_fail("��΢΢һЦ���ĵ�����ħ���������Ѿ����������У�\n");
			
		 break;
	    case "��ɽ��":
         if(me->query("quest/ssjf/jueji")=="pass")
           return notify_fail("��΢΢һЦ���ĵ�������ɽ���������Ѿ����������У�\n");           
		 break;
	    case "��ɽ��":
         if(me->query("quest/hsjf/fengyi5")=="pass")
			return notify_fail("��΢΢һЦ���ĵ�����Ҫ�������ƻ�ɽ�������������ڵ��죡\n");    
         //if(me->query("quest/hsjf/fengyi4_fail"))
			//return notify_fail("��Щ�ּ����������������У��˿���ֻ���о������֮����\n");    
         if(me->query("quest/huashan")!="����" ) 
			return notify_fail("����ǰ�������ۣ�û������ɶ����Ķ�������ʱ�����˰��죡\n");
		break;    
    }	

    tell_object(me,HIY"���־ٻ�ѣ�����ǰȥ������һ������������ʮ�������֣�\n\n"NOR);
    tell_object(me,HIR"                     ����\n"+
                      "                     �˳�\n"+
                      "                     �Ʒ�\n"+
                   HIM"                      ��\n"+
                      "                      ��\n"+
                   HIR"                      ��\n"+
                      "                      ɽ\n"+
                      "                      ��\n"+
                      "                      ��\n"+
                      "                      !\n"NOR);

    if (me->query("family/family_name")=="��ɽ��"&&me->query("quest/huashan")=="����"&&me->query_temp("hssb/juejiasked"))
       call_out("fengyi_quest1",2,me);
	if (me->query("family/family_name")=="�������" && me->query_temp("hssb/juejiasked"))
       call_out("tmgf_1",2,me); //������ħ��������
	
	me->delete_temp("hssb/juejiasked");

	return 1;
	//���ּ�2
  

}

//������ħ����
int tmgf_1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave" ) 
         return 1;
    
    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");
   
    write(HIY"�㲻�����м�̾��ϲ���ĵ��������Ž��г��ϴ��ţ�����������ֵܵĹ����ھ����£�\n"+
             "����һ����Ȼ�Ǳ�Ѱ���������Ƕ�����ʮ����Χ����ɽ�����䲻����ԭ�����Ǿ�Ȼ��\n"+
             "�����ڴˣ������컯Ū�ˣ�������ʮ�������ܵ��˼�����������������ǵ������似\n"+
			 "���ܻ��Ѳ�������\n"NOR);
    
    call_out("tmgf_2",5,me);
    return 1;
}

int tmgf_2(object me)
{
  
	if(file_name(environment(me))!="/d/huashan/cave") 
         return 1;

    write(HIC"\n����һ����,����˴�ʯ�����Ǽ�Ӳ��Ҫ����ʯ���ϻ�ͼд�֣�����������Ҳ��ʮ�ֲ�\n"
    "��!�����ٴ�ϸ�Ĳ쿴ʯ��������ͼ��,��֪Խ��Խ���ľ�,ʹ��������ֻ�ݲ����ʣ���\n"
    "����Ϊ��ª����������֮�п������ף������ǻ�ɽ���������Ʒ������������ӯ�鶯,\n"
    "��֮�Բ���������г��ŵ���һ��ֱ���εı��У���֪���ǰ�������ǹì���ۼ�ʹ����\n"
    "�εĹ�����������֮�������ǻ�ɽ�����Ŀ���,������Ƶľ��޻���֮����\n"NOR);
    //write(HIR"������ȫ���ע�о�����֮�ʣ���Ȼ��ܳ�������Ӱ����Χ��������\n"NOR);
    call_out("tmgf_3",2,me);
    return 1;
}

int tmgf_3(object me)
{
    int i;
	object cs_npc;
	if(file_name(environment(me))!="/d/huashan/cave" )
         return 1;

    write(HIR"�����´�ϲ,����̴��������书��ʽ�����������,�������˸���������?\n"
             "�㲻����Ҫ�о���͸�����������ħ�����Ǿ���ѧ�ɣ��ٽ������������Ϊ������ѧ������\n"+
			 "�������˼֮�ʣ���ʱ��Ȼ�ܳ����������˽���Χ��������\n"NOR);
    for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		//cs_npc->kill_ob(me);		
    }
  //  me->delete_temp("tmgf");
	
	me->set_temp("tmgf/killnpc",1);
    add_action("do_lianxi", "lianxi");

    return 1;
}


//���µ�����ϰ
int do_lianxi()
{
	int i,g,j;
	object me=this_player();
	
	if(file_name(environment(me))!="/d/huashan/cave" ){
		message_vision(HIY"��Ϊ�����е��ӣ���ս���ӣ��Ѿ��뿪��ɽ�ض�������ʧ�ܡ�\n"NOR,me);
        me->set("tmgf/jueji/time",time());
		me->add("tmgf/jueji/fail",1);
		
        return 1;
	}
	if (me->query("quest/hmy/dlsmf/pass")||me->query_skill("dali-shenmofu",1))
	{
		message_vision(HIC"����ϰһ����ħ��������Ȼ������Ѫ��ӿ��ԭ���Ǻ���ǰ��ϰ�Ĵ�����ħ��ͷ������������\n"NOR,me);
		return 1;
	}
	if (present("gao shou",environment(me)))
	  return notify_fail("�㻹û��ɱ����Щ���֣�����ܾ������������ħ����\n");
	if (!me->query_temp("tmgf/killnpc"))
	  return notify_fail("��Ҫ��ϰʲô��\n");
	//if(arg !="����" && arg != "����" && arg !="������ħ����")
        //return notify_fail("��Ҫͨ����ϰ������ʲô��\n");
	if (me->query("quest/hmy/tmgf/jueji")=="pass")
	   return notify_fail("���Ѿ���ȫ������ħ�����������������˷�ʱ�䣡\n");
	
	if ((time()-me->query("tmgf/jueji/time"))<86400)
	    return notify_fail("������̫Ƶ���ˣ�\n");
	if(me->query("dex")<40)
    {
    	write("��ħ����Ҫ���ߵ���������40������ʩչ����������������̫�ͻ��ǸϽ�����ȥ�ɡ�\n");
		return 1;
	}
	if(me->query_skill("tianmo-gun",1)<450)
    {
    	
    	write("��ħ��û�д�ɣ��Ͻ�����ȥ�ɡ�\n");
		return 1;
	}
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	//g=random(me->query("relife/gifts/total"));
	

	message_vision(HIC"$N���Է������Ļ���������������ϵ���ƣ����ɵ����˿ڳ��������ٿ���ʹ�����Σ�����������һ�ţ�\n"+
					  "��ʽ�����Źۣ�һ���м��޷��İ�����̬��$N������Ц��ͻȻ֮�䣬����Ц�ݽ�Ӳ������������һ�������\n"+
					  "��ëֱ������Ŀ��ת˲�����������������ֹ�����Խ��Խ���������������λʵ������˼�����\n"NOR,me);
	
	if (me->query("kar")<31
		&& random(me->query("kar"))>25
		&& i<4
		&& random(me->query("dex"))>40
		&& me->query("dex")>=40)
	{
       message_vision(HIW"$N��Ȼ��������ħ��Ҫ�����ɾ���һ��֮����������Ҫ���Ǻܸߵġ�\n"NOR,me);
	   message_vision(HIY"�Է�������ʽѸ���ޱȣ���ÿһ���Ʊض����������֮�ϣ�������迴֮�¡�\n"+
						"���Ǽ�׾��ȴ�˼��ɣ�����������ʵ����ǿ�����浽�ˡ��Ծ��ƶ�����׾���ɡ��ļ��衣��\n"NOR,me);
	   message_vision(HIC"$N��ϲ�㣬����ǧ�����գ�����������ħ�����������С�\n"NOR,me);
	  
	   log_file("quest/tmgfjueji",sprintf("%s(%s) �ڻ�ɽʯ�ڣ�����������ħ����������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("tmgf/jueji/fail"),me->query("combat_exp"),g,me));
	   me->set("title",HIY"�������"HIC"��Գ��ħ"NOR);
	   me->set("quest/hmy/tmgf/jueji","pass");
	   me->delete_temp("tmgf/killnpc");
	   me->delete_temp("hssb/juejiasked");
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N��Ȼ֪����ħ������ʽ�����������ʹ�õľ�������һʱ֮��ȴ��������⡣\n"
		                      +"��ħ����������û�з��ӳ����������㻹���д�����������ɽʯ������ѧϰ�ˡ�\n"NOR,me);
		log_file("quest/tmgfjueji",sprintf("%8s%-10s�ڻ�ɽʯ�ڣ�������ħ����������û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("tmgf/jueji/fail"),me->query("combat_exp"),g,me));
		me->add("tmgf/jueji/fail",1);
		me->set("tmgf/jueji/time",time());
		me->delete_temp("tmgf/killnpc");
	    me->delete_temp("hssb/juejiasked");
		me->start_busy(1);
        return 1;
	}
	
}

//���ܻ�ɽ��������4����
int fengyi_quest1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave") 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    write(HIW"�㲻����Ȼ��ŭ���ĵ������޳��󱲣��󵨿����Ѽ�����ɽ������΢�����\n"+
             "���ܵ���ס������ָ��������˭����˵����һ�����ơ��֣�����˭����˵�ǡ�\n"+
             "���ơ�����\n"NOR);

    call_out("fengyi_temp",3+random(5),me);
    return 1;
}

int fengyi_temp(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave") 
         return 1;

    write(HIC"\n����һ����,����˴�ʯ�����Ǽ�Ӳ��Ҫ����ʯ���ϻ�ͼд�֣�����������Ҳ��ʮ�ֲ�\n"
    "��!�����ٴ�ϸ�Ĳ쿴ʯ��������ͼ��,��֪Խ��Խ���ľ�,ʹ��������ֻ�ݲ����ʣ���\n"
    "����Ϊ��ª����������֮�п������ף������ǻ�ɽ���������Ʒ������������ӯ�鶯,\n"
    "��֮�Բ���������г��ŵ���һ��ֱ���εı��У���֪���ǰ�������ǹì���ۼ�ʹ����\n"
    "�εĹ�����������֮�������ǻ�ɽ�����Ŀ���,������Ƶľ��޻���֮������ʱ�䣬��\n"
    "���ɶԱ����书����ȫʧ��\n\n"NOR);

    call_out("fengyi_temp2",3+random(5),me);
    return 1;
}

int fengyi_temp2(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave")
         return 1;

    write(HIM"�����´�,�ѵ����ɴ��������书���е�����˲���,���˸���������ȥ?\n"
             "�㲻����Ҫ��ʯ���ϵĽ����о���yanjiu����͸�����⻪ɽ�����ѵ������˲���һ������\n\n"NOR);

    me->set_temp("quest/huashan/fengyi_yanjiu",1);
    add_action("do_yanjiu", "yanjiu");

    return 1;
}
//��ɽ�����о�
int do_yanjiu(string arg)
{
    object me = this_player();
    int i;

    if(!me) return 0;

    if(!me->query_temp("quest/huashan/fengyi_yanjiu"))
        return notify_fail("�㻹�п��о����������ר�������Լ�����ȥ��\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    if(!arg) return notify_fail("��Ҫ�о�ʲô��\n");

    if(arg!="���� at ʯ��")
        return notify_fail("��Ҫ�о�����Ķ�����\n");

    if((int)me->query_skill("huashan-jianfa",1)<450)
        return notify_fail("��Ļ�ɽ����ʵ��̫��,������ʯ���ϵľ����!\n");

    if(me->query("quest/hsjf/fengyi4")=="pass")
        return notify_fail("���Ѿ���͸���з����ǡ��ĵ��ĺ�����!\n"NOR);

    if((int)me->query("quest/hsjf/fengyi4_time")+86400 > time())
        return notify_fail("��ող��о������У���������Ϣ�°ɣ�\n");

    if((int)me->query_temp("quest/huashan/fengyi_yanjiu")<5){
        i = (int)me->query_skill("huashan-jianfa",1);
        i = i*i/7;
        me->add_temp("quest/huashan/fengyi_yanjiu",1);
        me->add("jingli",-(int)me->query("eff_jingli")/5);
        me->add("jing",-500);
        me->add("neili",-600);
        me->add_busy(3+random(3));   
        return notify_fail(HIY"����ϸ���о���ʯ���ϵĽ��У��������������ʧ���Ѿã����о�����ף�\n"NOR);
    }
    if(random((int)me->query_temp("quest/huashan/fengyi_yanjiu")+1)<5){
        if((int)me->query_temp("quest/huashan/fengyi_yanjiu")>=6 || random(me->query("kar"))<26){
            me->start_busy(2);
            me->add("quest/hsjf/fengyi4_fail",1);
            me->set("quest/hsjf/fengyi4_time",time());
            me->set("quest/hsjf/fengyi4_exp",me->query("combat_exp"));
            me->delete_temp("quest/huashan/fengyi_yanjiu");
            log_file("quest/fengyi", sprintf(HIR"ʧ�ܣ��з�����Quest��¼��%s(%s)�ڻ�ɽ�ض������ĺ���ʧ�ܡ�����%d��\n"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
            return notify_fail(HIR"���˺þã�������Լ��Ļ�ɽ�������軹��̫�ͣ��޷����ʯ���ϵľ������У�\n"NOR);
        }
        i = (int)me->query_skill("huashan-jianfa",1);
        i = i*i/7;
        me->add_temp("quest/huashan/fengyi_yanjiu",1);
        me->add("jingli",-(int)me->query("eff_jingli")/5);
        me->add("jing",-500);
        me->add("neili",-600);
        me->add_busy(3+random(3));
  
        return notify_fail("����ϸ˼�������ã����ֶԻ�ɽ��������ʶ�ֽ���һ����\n");
    }
    else{
            me->set("quest/hsjf/fengyi4","pass");
			
            me->set("quest/hsjf/fengyi4_exp",me->query("combat_exp"));
            me->set("quest/hsjf/fengyi4_time",time());
            me->delete_temp("quest/huashan/fengyi_yanjiu");
            me->start_busy(2+random(2));
            write(HIC"\n��ͻȻ��ʯ���Ϸ����ˡ��з����ǡ���һ�У���֪���н����˲�������У�����δ��͸��\n"+
                       "�����к͵����С�������ʯ����ʹ��֮�ˣ�������ӯ�鶯��������Ϊ�Źֵ�ȴ�����ޱȡ�\n"+
                  HIR"\n���£���ͻȻ���򵽣����������ģ���ȴ�ǻ�ģ���ɽ���������뽣��֮����νӱ仯��\n"+
                       "��һ�ɲ���ģ���������ߣ����Ķ�����������Ȼ�νӵ������޷죬������ϳɵĻ�ɽ��\n"+
                       "������\n"+
                  HIY"\n�����򵽴ˣ��������ǡ����ơ����֣��������ƽ���֮�˸е���Ц�¼�!\n"NOR);
            log_file("quest/fengyi", sprintf(HIG"�ɹ����з�����Quest��¼��%s(%s)�ڻ�ɽ�ض��ɹ�����з����ǵ��ĺ��С�����%d��\n"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
            return 1;
    }
}
