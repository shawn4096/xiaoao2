// Room: /d/huashan/cave1.c
// Date: sohu@xojh
// ������ħ������ɽ�����߼�quest

#include <ansi.h>
string look_dazi();
int dlsmf_1(object me);
int dlsmf_2(object me);
int dlsmf_3(object me);
int do_lianxi();
inherit ROOM;
//#include "fengyi5.h"
void create()
{
        set("short", "�ܶ�");
        set("long",@long
���߽���������ʯ�ں��棬���ж��죬�Ǹ����ݵ�ǧ��֮�ڵĴ󶴣�����
���߾ߺ��ǣ����������ԣ����Ծ��б��С�ɽ���ı��������ͻ��һ���ʯ��
����һ��ƽ̨����ʯ֮�¿���ʮ��������(dazi)��������Ѹ���ʯ�����տ�
ʱ��ֻ��һ���̵ֿ��������Ժ�����ɽ�����ڴˡ���һ��֮�Ե�ʯǽ(wall)֮
�Ͽ����������Σ�����һ�ƣ���˵Ҳ�������ٸ�����Ȼ��ʹ�����������ƽ�ʹ
�����εĽ�������Щ����֮�ԣ���Ȼ����һ���ּ�(ziji)���㲻���뿴(kan)
���д��Щʲô��
long);
        set("exits", ([
              //  "out" : __DIR__"rukou",
			    "west" : __DIR__"cave",
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
    //object me=this_player();
//add_action("do_lianxi", "lianxi");
    add_action("do_kan", "kan");

}

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
//���⿪���ӣ��򲻻�����ּ���
    switch (me->query("family/family_name"))
    {
      case "�������":
        //if(me->query("quest/hmy/tmgf/jueji")=="pass")
          //return notify_fail("�㿴��ǽ�ϵ���ʽ����Ȼȫ����Ϥ���ĵ�����ħ���������Ѿ����������У�\n");  
        if(me->query("quest/hmy/dlsmf/jueji")=="pass")
          return notify_fail("��΢΢һЦ���ĵ���������ħ�������Ѿ����������У�\n");				
		
		break;
	  case "��ɽ��":
        if( me->query("quest/ss/ssjf/jueji/pass"))
          return notify_fail("��΢΢һЦ���ĵ�������ɽ���������Ѿ����������У�\n");           
		break;
	
    }	
        tell_object(me,YEL"������ѣ�����ǰȥ������һ������������ʮ�����֣�\n\n"NOR);
        tell_object(me,HIC"                     ����\n"+
                          "                     �ɺ�\n"+                   
                       HIR"                      ��\n"+
                          "                      ��\n"+
                       HIC"                      ��\n"+
                          "                      ɽ\n"+
                          "                      ��\n"+
                          "                      ��\n"+
                          "                      !\n"NOR);
   
	
	me->set_temp("hssb/lookzi1",1);
	if (me->query_temp("hssb/juejiasked")&&me->query("family/family_name")=="��ɽ��")
	{
		message_vision(HIY"\n\n$N���������֣���ʱ��Ȼ��ŭ����Ȼ�ȵ������������֪֮ͽ����Ȼ�Һųƾ�����ɽ��������\n"NOR,me);
		message_vision(HIC"\n\n\n$NԽ��Խ�����̲�ס�����ѣ���סǽ�ڹۿ�����...��\n"NOR,me);

		me->start_busy(3);
		me->delete_temp("hssb/juejiasked");
		//remove_call_out("ssjf/quest");
		call_out("ssjf_quest",3+random(3),me);
		//me->set_temp("hssb/loo");
	}
    add_action("do_chuaimo", "chuaimo");
	return 1;
		
}

//���ܴ�����ħ��ͷ
int do_chuaimo(string arg)
{
    object me = this_player();
    if (!me->query_temp("hssb/lookzi1"))
       return notify_fail("��û��Ϲ��Ħʲô��\n");
    if(!arg)
        return notify_fail("��Ҫ��Ħʲô��\n");

    if(arg!="������ħ��" && arg!="����")
        return notify_fail("��Ҫ��Ħʲô��\n");
    //����ħ����ͻ
	if(me->query_skill("tianmo-gun",1)>1){
       
        return notify_fail(HIR"�������ʯ���ϵĸ�������Ħ����Ħȥ�������޷�Ū�����㴧Ħ���÷������ף�ԭ���Ǻ��Լ���ѧ����ħ�������ͻ��\n"NOR);
    }
	if(me->query_skill("qixian-wuxingjian",1)>1){
       
        return notify_fail(HIR"�������ʯ���ϵĸ�������Ħ����Ħȥ�������޷�Ū�����㴧Ħ���÷������ף�ԭ���Ǻ��Լ���ѧ���������ν����ͻ��\n"NOR);
    }
/*	if (me->query("quest/hmy/dlsmf/pass") )
	{
		message_vision(HIC"�㴧Ħ���ã��Դ�����ħ��ͷ�������á�\n" NOR,me);
		me->improve_skill("dali-shenmofu",random(me->query_int(1)));
		return 1;

	}*/
	if (!me->query_skill("dali-shenmofu"))
	{	
      if ((time()-me->query("quest/hmy/dlsmf/time"))<86400 )
	    return notify_fail("������Ҳ̫�ڿ���ˣ�\n"); 
	  //if (me->query("kar")>1 && random(10)>1)
	  if (me->query("kar")>28 && random(10)>7)     
	  {
	
        write(HIG"�������ʯ���ϵĸ�ͷ��ʽ,����������ͻȻ�����һ������ʱ�����\n"+
                 "�⡰������ħ��������ʽ���㲻��������Ц����������~��ԭ����˰�!��\n"NOR);

        me->set("quest/hmy/dlsmf/pass",1);
        me->improve_skill("dali-shenmofu",20);
        log_file("quest/dlsmfu", sprintf("������ħ�����ܳɹ���¼��%s(%s)�ڻ�ɽ�ض�ʧ��%d�κ�Ħ������ħ���ɹ�������%d��\n"NOR, me->name(1),me->query("id"), me->query("quest/hmy/dlsmf/fail"), me->query("combat_exp")) );
        return 1;
      }
	  else {
	  
       write(HIY"�������ʯ���ϵ���ʽ��������Ħ������ħ���У���Ȼ�����е�˼·���������޷����͸����\n"NOR);
       me->add("quest/hmy/dlsmf/fail",1);
	   me->set("quest/hmy/dlsmf/time",time());
	   me->delete_temp("hssb/lookzi1");
       log_file("quest/dlsmfu", sprintf("%s(%s)�ڻ�ɽ�ض���Ħ������ħ��ͷ����ʧ��%d�Ρ�����%d��\n"NOR, me->name(1),me->query("id"),me->query("quest/hmy/dlsmf/fail"), me->query("combat_exp")) );
       return 1;
	  }
	  
	  //�������ͨ��
    }else if ((me->query_skill("dali-shenmofu",1)<450))
    {
      
	   write(YEL"�������ʯ���ϵ���ʽ��������Ħ������ħ���У�ҡͷ���ԣ��ƺ������ĵã�\n"NOR);
	   me->improve_skill("dali-shenmofu",me->query_int()/2);
	   me->receive_damage("jing",random(20));
	   me->start_busy(random(1));	   

	}
	//450�󷽿���ϰ����
    else
      {
	   me->delete_temp("hssb/lookzi1"); 
	   me->set_temp("dlsmf/yanjiu",1);
	   message_vision(HIG"$N���������Լ���������ʽ�������Ѿ���ϰ�������ֻ���һ����Ҫͨ���о�(yanjiu)����ϰ�á�\n"NOR,me);
	   add_action("dlsmf_yanjiu", "yanjiu");
	   return 1;
       }
   // return 1;
}
//���ܾ���
int dlsmf_yanjiu(string arg)
{
	object me=this_player();
	if (!me->query_temp("dlsmf/yanjiu"))
	    return notify_fail("����㱾�»��о�ʲô��\n");
	if(arg!="��ħ" && arg!="����" && arg!="������ħ������")
        return notify_fail("��Ҫ�о�ʲô��\n");
	if(me->query_temp("dlsmf/chuaimo"))
        return notify_fail("�����ڴ�Ħ�����У�\n");
	
	write(HIC"��۾�����������ʯ���ϴ�����ħ��ͷ���һ�е���ʽ�������ĵã�\n"NOR);
	me->start_busy(1);
	if ((int)me->query_skill("dali-shenmofu",1)>450 && !random(5))
	{
		me->set_temp("dlsmf/chuaimo",1);
		
		call_out("dlsmf_1",2,me);
		
	}
   
   return 1;


}
int dlsmf_1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1" ) 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");
   

    write(HIY"�㲻�����м�̾��ϲ���ĵ��������Ž��г��ϴ��ţ�������д�����ħ���ľ�����\n"+
             "��������̴�����ħ���ɳ�����������ϧ����Χ����ɽ�����䲻����ԭ�����ǡ�\n"+
             "��Ȼ�����ڴˣ������컯Ū�ˣ�������ʮ�������ܵ��˼�����������������ǵ�\n"+
			 "������������ܻ��Ѳ�������\n"NOR);
    
    call_out("dlsmf_2",5,me);
    return 1;
}


int dlsmf_2(object me)
{
  
	if(file_name(environment(me))!="/d/huashan/cave1") 
         return 1;

    write(HIC"\n����һ����,����˴�ʯ�����Ǽ�Ӳ��Ҫ����ʯ���ϻ�ͼд�֣�����������Ҳ��ʮ�ֲ�\n"
    "��!�����ٴ�ϸ�Ĳ쿴ʯ��������ͼ��,��֪Խ��Խ���ľ�,ʹ��ͷ������ֻ�ݲ����ʣ���\n"
    "����Ϊ��ª����������֮�п������ף������Ǵ�����ħ������ʽ����ʽ��Ȼ��Ϊ��,����\n"
    "��֮�Բ���������г��ŵ���һ�ѿ�����Ȼ����ɽ�Ķ��ű��������ܶԷ��Ľ���Ϭ������\n"
    "�����⸫ͷ����ʽ�¶Է��Ľ���������Ƶľ��޻���֮������ʱ�䣬��·𿴵�һ��ǰ��δ��\n"
    "����ѧ���磬һ����ʮ�ᣡ\n\n"NOR);
    //write(HIR"������ȫ���ע�о�����֮�ʣ���Ȼ��ܳ�������Ӱ����Χ��������\n"NOR);
    call_out("dlsmf_3",2,me);
    return 1;
}

int dlsmf_3(object me)
{
    int i;
	object cs_npc;
	if(file_name(environment(me))!="/d/huashan/cave1" )
         return 1;

    write(HIR"�����´�ϲ,���ɴ��������书��ʽ�����������,�������˸���������?\n"
             "�㲻����Ҫ�о���͸�����������ħ�����Ǿ���ѧ�ɣ��ٽ������������Ϊ������ѧ������\n"+
			 "�������˼֮�ʣ���ʱ��Ȼ�ܳ����������˽���Χ��������\n"NOR);
    for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		
		cs_npc->set("combat_exp",me->query("combat_exp")*4/3);
        cs_npc->set("qi",me->query("qi")*3/2);
		cs_npc->set("max_neili",me->query("max_neili"));
		
    }
    me->delete_temp("dlsmf/chuaimo");
	//me->delete_temp("");
	me->set_temp("dlsmf/fightnpc",1);
    add_action("do_lianxi", "lianxi");

    return 1;
}
int do_lianxi()
{
	int i,g,j;
	object me=this_player();
	me->start_busy(10);
	if(file_name(environment(me))!="/d/huashan/cave1" ){
		message_vision(HIY"��Ϊ�����е��ӣ���ս���ӣ��Ѿ��뿪��ɽ�ض�������ʧ�ܡ�\n"NOR,me);
        me->set("dlsmf/jueji/time",time());
		me->add("dlsmf/jueji/fail",1);
		
        return 1;
	}
	if (present("gao shou",environment(me)))
	  return notify_fail("�㻹û��ɱ����Щ���֣�����ܾ������������ħ����\n");
	
	//if(arg !="����" && arg != "����" && arg !="������ħ����")
        //return notify_fail("��Ҫͨ����ϰ������ʲô��\n");
	if (me->query("quest/hmy/dlsmf/jueji")=="pass")
	   return notify_fail("���Ѿ���ȫ���������ħ�����������˷�ʱ�䣡\n");
	
	if (time()-me->query("dlsmf/jueji/time")<86400)
	    return notify_fail("������̫Ƶ���ˣ�\n");
	if(me->query("str")<40)
    {
    	
    	write("������ħ��ͷ��Ҫ���ߵ����������40������ʩչ�����������������̫�ͻ��ǸϽ�����ȥ�ɡ�\n");
		return 1;
	}
	if(me->query_skill("dali-shenmofu",1)<450)
    {
    	
    	write("������ħ����û�д�ɣ��Ͻ�����ȥ�ɡ�\n");
		return 1;
	}
  //  i=random(10);
//	j=random(me->query("kar"));
	//g=random(me->query("relife/gifts/total"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	
	if (me->query("kar")<31
		&& random(me->query("kar"))>28
		&& i<3
		&& random(me->query("str"))>40)
	{
       message_vision(HIC"$N��Ȼ�����������ħ��Ҫ�����ɾ���һ��֮�������ڱ���Ҫ���Ǻܸߵġ�\n"NOR,me);
	   message_vision(HIY"$N����ʲô�鶯���ǹ��죬��ֻ��һ��ͷ����ȥ�����ˣ�\n"NOR,me);
	   message_vision(HIG"$N��ϲ�㣬����ǧ�����գ��������������ħ��ͷ���������С�\n"NOR,me);
	  
	   log_file("quest/dlsmfjueji",sprintf("%s(%s) �ڻ�ɽʯ�ڣ��������������ħ����������Դ��%d�������i��%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("dlsmf/jueji/fail"),me->query("combat_exp"),g,me));
	   me->set("title",HIY"�������"HIR"������ħ"NOR);
	   me->set("quest/hmy/dlsmf/jueji","pass");
	   me->delete_temp("dlsmf/fightnpc");
	
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N��Ȼ֪��������ħ������ʽ�����������ʹ�õľ�������һʱ֮��ȴ��������⡣������ħ����\n"
		                      +"������û�з��ӳ����������㻹���д�����������ɽʯ������ѧϰ�ˡ�\n"NOR,me);
		log_file("quest/dlsmfjueji",sprintf("%8s%-10s�ڻ�ɽʯ�ڣ����������ħ��������û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("dlsmf/jueji/fail"),me->query("combat_exp"),g,me));
		me->add("dlsmf/jueji/fail",1);
		me->set("dlsmf/jueji/time",time());
		me->delete_temp("dlsmf/fightnpc");
	
		me->start_busy(1);
        return 1;
	}
	

}

//������ɽ��������

int ssjf_quest(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1") 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    write(HIC"�㲻����Ȼ��ŭ���ĵ������޳��󱲣��󵨿����Ѽ�����ɽ������΢�����\n"+
             "���ܵ���ס������ָ��������˭����˵����һ�����ơ��֣�����˭����˵�ǡ�\n"+
             "���ơ�����\n"NOR);
    call_out("ssjf_temp",5,me);
    return 1;
}


int ssjf_temp(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1") 
         return 1;

    write(HIY"\n����һ����,����˴�ʯ�����Ǽ�Ӳ��Ҫ����ʯ���ϻ�ͼд�֣�����������Ҳ��ʮ�ֲ�\n"
    "��!�����ٴ�ϸ�Ĳ쿴ʯ��������ͼ��,��֪Խ��Խ���ľ�,ʹ��������ֻ�ݲ����ʣ����������ʲݣ�\n"
    "��������֮�п������ף���������ɽ���������Ʒ���������������磬������ɽ������·,ϸ��֮�¡�\n"
    "��֮�Բ���������г��ŵ���һ��ֱ���εı��У���֪���ǰ����������������ۼ�ʹ��֮��\n"
    "�ε����𵲷���������֮����������ɽ�����Ŀ���,������Ƶľ��޻���֮������ʱ�䣬��\n"
    "���ɶԱ����书����ȫʧ��\n\n"NOR);

    call_out("ssjf_temp2",2,me);
    return 1;
}

int ssjf_temp2(object me)
{
    object cs_npc;
	int i;
	if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1")
         return 1;

    write(HIG"\n\n�����´�,�ѵ����ɴ��������书���е�����˲���,���˸���������ȥ?\n"
             "�㲻����Ҫ�о���yanjiu����͸��������ɽ�����ѵ������˲���һ������\n\n"NOR);
	
	write(HIR"\n\n\n�����´�ϲ,���ɴ��������书��ʽ�������Ϭ��,�������˸���������?\n"
             "�㲻����Ҫ�о���͸��������ɽ�������Ǿ���ѧ�ɣ��ٽ������������Ϊ������ѧ������\n"+
			 "�������˼֮�ʣ���ʱ��Ȼ�ܳ����������˽���Χ��������\n"NOR);
    
	for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		
		cs_npc->set("combat_exp",me->query("combat_exp")*4/3);
        cs_npc->set("qi",me->query("qi")*3/2);
		cs_npc->set("max_neili",me->query("max_neili"));
		
    }
    me->set_temp("hssb/yanjiu",1);
	me->delete_temp("hssb/lookzi1");
    add_action("do_yanjiu", "yanjiu");
    return 1;
}

int do_yanjiu(string arg)
{
    object me = this_player();
    int i;

    if(!me) return 0;

	if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1")
         return 1;
	if (!me->query_temp("hssb/yanjiu"))
	    return notify_fail("��Ҫ��ʲô��!\n");  

    me->delete_temp("hssb/yanjiu");	
	
    if (present("gao shou",environment(me)))
	  return notify_fail("�㻹û��ɱ����Щ���ɸ��֣�����ܾ����о���ɽ�������У���\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("����æ���أ�\n");

    if(!arg) return notify_fail("��Ҫ�о�ʲô��\n");

    if(arg!="��ɽ����" && arg!="��ɽ����")
        return notify_fail("��Ҫ�о������ʲô������\n");

    if((int)me->query_skill("songshan-jian",1)< 450)
        return notify_fail("�����ɽ����ʵ��̫�����450��,������ʯ���ϵľ����!\n");

    if( me->query("quest/ss/ssjf/jueji/pass"))
        return notify_fail("���Ѿ���͸����ɽ��������������ʽ��!\n"NOR);

    if(time()-(int)me->query("quest/ss/ssjf/jueji/time")<86400 )
        return notify_fail("��ող��о������У���������Ϣ�°ɣ�\n");

    message_vision(HIC"\n\n$N��ϸ���о���ʯ���ϵĽ��У��������������ʧ���Ѿã����о�����ף�\nͬʱ$N���ж�ʱ������֣���Щ��ʽ��Ȼ��ʦ������֪����\n"NOR,me);
	i=me->query("int");
/*
	if (me->query("kar")<31
		&& random(me->query("kar"))>25
		&& i<3
		&& random(me->query("int"))>40)		*/
	if (me->query("kar")<31
		&& random(me->query("kar"))>26)
	{
		 write(HIC"\n��ͻȻ��ʯ���Ϸ����ˡ��ݺ����ء���һ�У���֪���н����˲��������У�����δ��͸���������ʽ��\n"+
                  "������ʯ����ʹ��֮�ˣ�������ӯ�鶯��������Ϊ�Źֵ�ȴ�ۻ������������ɽ�����ľ������ڡ�\n"+
               HIR"\n���£���ͻȻ���򵽣�ʦ����Ȼû�д��ڸ��Լ��أ������֮ʱ��ϲ��������Խ��ȴԽ���ú�Ϳ��\n"+
                  "����ʶģ����ɽ������������ߣ����Ķ�������֪��������ϳɵ���ɽ����������Ϊ����ô����ʽ��\n"+
                  "�������뵽�׷����ӵĽ���֮�У�ʱ������ɽ������ʱ����ħ�̳��ϵĹ������������߻���ħ֮״��\n"+
               HIY"\n\n\n\������������ã֮�ʣ�����������Ȼ���������������˹����������򵽴ˣ��������ǡ����ơ�����.\n"+
					"������������ɽ���е�ħ�̳��ϸе��������ֺ��£�˼ǰ��󣬻��Ǿ�����ȥ���ʦ��Ϊ��!\n"NOR);
		me->set_temp("quest/ss/ssjf/jueji/hssb",1);
		me->set("quest/ss/ssjf/jueji/hssb",1);
		me->set("quest/ss/ssjf/jueji/time",time());
		log_file("quest/ssjfjj", sprintf("�ɹ���%8s(%8s) ʧ��%d�κ󣬿����˻�ɽʯ����ɽ�似��i�������ԣ�%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );

	}else {

		write(HIY"�㿴�˰��죬�վ������뵽��ʽ֮�У�ʱ���˷ܣ�ʱ��ʧ�䣬�����߻���ħ֮״̬��\n"NOR);
		message_vision(HIR"$N��Ȼ����ȫ���������ߣ��۵�һ��ͻ��һ����Ѫ����Ȼ���˲��ᡣ\n"NOR,me);
		message_vision(HBBLU+HIW"����ʧ�ܣ�����������\n"NOR,me);

		me->apply_condition("neishang",5);
		me->apply_condition("liuxue",5);
		me->add_busy(4);
		me->set("quest/ss/ssjf/jueji/time",time());
		me->set("quest/ss/ssjf/jueji/combat",me->query("combat_exp"));
		me->set("quest/ss/ssjf/jueji/giftint",me->query("int"));
		me->add("quest/ss/ssjf/jueji/fail",1);
		log_file("quest/ssjfjj", sprintf("�ɹ���%8s(%8s) ʧ��%d�κ���Ȼû������ɽʯ����ɽ�������i�������ԣ�%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );

	}
	
    return 1;
}


