#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�϶��ֽ�");
        set("long", @LONG
�����Ǿ���������������ͨ�����źͶ��ŵĶ���·�ڣ���ʱ���ж������
��ʿ��������ȥ�����ϳ��ǿ���ȥ���ϣ��򶫳��ǿ���ȥ���ա����ա����淽
����һ���ߴ����¥��
LONG
        );
        set("outdoors", "����");
        set("xyjob",1);
        set("exits", ([
                "east" : __DIR__"djie1",
                "north" : __DIR__"dpailou",
		"west" : __DIR__"njie1",
        ]));
        set("objects",([
		__DIR__"npc/wuxiuwen" : 1,
			__DIR__"npc/xyxunbu" : 1,
        ]));
        set("incity",1);
	setup();
}


void init()
{
             object me = this_player();
             int time,total ;
			 int maxjl,maxnl;
             string vip;
             if(!userp(me)) return;
        /*    if(me->query_condition("db_exp",1)>10000)
                me->apply_condition("db_exp", 10000);
             if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	    */	//else
              //  me->add_condition("db_exp", 10000);
             //if(me->query("combat_exp")<100000) me->apply_condition("db_exp", 1000);
            // time = me->query("vip/vip_time") - time();
/*    
        if((me->query("str")> 32 
	  || me->query("int")> 32
	  || me->query("con")>32 
	  || me->query("dex")> 32 ) 
         && me->query("combat_exp")<=12000000 ) {
      me->move("d/wizard/xhw");
      tell_object(me, "����Ϊ�츳�쳣����Ҫ���е�����飬��ʱ��������ɡ�\n");	

}*/
//�Զ�����vip
if( me->query("rmb_used")>=500  && !me->query("buyvip/start") ) me->set("buyvip/start",1);
if(!me->query("cw_exp"))  me->delete("relife/exp_ext");
//������Ϊ���������⵼�µı�ǻ���

if (me->query("buyvip"))
{
	me->delete("m-card-vip");
	//write("��Ϊ������������ɾ���¿����\n");
	me->delete("y-card-vip");
	//write("��Ϊ������������ɾ���꿨���\n");
	if (me->query("vip/vip_time")-time()<86400)
	{
		me->set("vip/vip_start_time",time());    
		me->set("vip/vip_time",time());   
		me->add("vip/vip_time",3*365*24*3600);
	}
	

}
else if (me->query("y-card-vip"))
{
	me->delete("m-card-vip");	
	//write("��Ϊ�����꿨������ɾ���¿����\n");
}
//������Ϊ������ɵ�id��������;������


	maxnl=(int)(me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
	maxjl=(int)(me->query_skill("force")-me->query_temp("apply/force")) * 8;

/*
time = time() - me->query("char_check",1);	
total =  me->query("SJ_Credit",1)+me->query("SJ_Credit_Used",1);

if( time >=86400 ){
  
  if(me->query("registered")<=3) vip =HIG"��ͨ��Ա"NOR;
  if(me->query("m-card-vip"))   vip =HIM"�¿����"NOR;
  if(me->query("y-card_vip")==1)   vip =HIR"�꿨���"NOR;
  if(me->query("buyvip"))       vip =HIW"�������"NOR;
  	
  me->set("char_check",time());

 tell_object(me,HIG"���ڿ�ʼ�˲�����״̬����\n��Ŀǰ��ʣ"
          + chinese_number(me->query("SJ_Credit"))+"���齣ͨ�������Ѿ��ۼ�������" 
           + chinese_number(me->query("SJ_Credit_Used")) +"���齣ͨ����\n"NOR);
 log_file( "static/check_CREDIT",sprintf("%s(%s)  | ʣ��:%s  �ۼ�ʹ��:%s,�ܼ�ӵ��%d�������츳%d������EXP%d������ȼ�%s��Ŀǰ����%d��\n", 
             me->name(),
             me->query("id"),
             chinese_number(me->query("SJ_Credit")),
             chinese_number(me->query("SJ_Credit_Used")),
              total,
              me->query("relife/gifts/total"),
              me->query("relife/exp_ext"),
              vip,
              me->query("combat_exp")
              
              
              
              
                      ));
            }
*/
//��ʱ������������30
	//if (me->query_skill("liumai-shenjian",1)>30)
	    // me->set_skill("liumai-shenjian",30); 

	if (!me->query("quest/jiuyin1/pass")){
      if( me->query_skill("jiuyin-zhengong",1)>221) me->set_skill("jiuyin-zhengong",221); 
      if( me->query_skill("jiuyin-shenfa",1)>221) me->set_skill("jiuyin-shenfa",221);
	}
//�޸�����¼bug����

	if(me->query("registered")<=3) vip =HIG"��ͨ��Ա"NOR;
	if(me->query("m-card-vip"))   vip =HIM"�¿����"NOR;
	if(me->query("y-card_vip"))   vip =HIR"�꿨���"NOR;
	if(me->query("buyvip"))       vip =HIW"�������"NOR;
	
/*
	if(me->query_condition("db_exp",1)<10)
	{
		//tell_object(me,HIY"���˫�������쳣���뼰ʱ����ʦ��ϵ�����������Ϣ�Ѿ���¼�ڰ���\n"NOR);
		//me->set("bug/db_exp",me->query_condition("db_exp"));
		me->apply_condition("db_exp",10000);
	}
*/	
/*
if (me->query("buyvip") && me->query("SJ_Credit")>75000)
	{
		tell_object(me,HIR"����"+vip+HIR"��ݣ������ͨ���쳣�����ڶ�Ϊ"+me->query("SJ_Credit")+HIR"�뼰ʱ����ʦ��ϵ�����������Ϣ�Ѿ���¼�ڰ���\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",60000);
		log_file("quest/edittongbao", sprintf("%s(%s) ��ʱ��ͨ��Ϊ%d����˫�����飺%d����ǰ���飺%d��VIP���Ϊ%s��\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );
		//tell_object(me,HIY"���ͨ���쳣���뼰ʱ����ʦ��ϵ�����������Ϣ�Ѿ���¼�ڰ���\n"NOR);

	}
	if (me->query("y-card_vip")&&me->query("SJ_Credit")>20000)
	{
		tell_object(me,HIR"����"+vip+HIR"��ݣ������ͨ���쳣�����ڶ�Ϊ"+me->query("SJ_Credit")+HIR"�뼰ʱ����ʦ��ϵ�����������Ϣ�Ѿ���¼�ڰ���\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",8000);
		log_file("quest/edittongbao", sprintf("%s(%s) ��ʱ��ͨ��Ϊ%d����˫�����飺%d����ǰ���飺%d��VIP���Ϊ%s��\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );

	}
	if (me->query("m-card_vip")&&me->query("SJ_Credit")>2500)
	{
		tell_object(me,HIR"����"+vip+HIR"��ݣ������ͨ���쳣�����ڶ�Ϊ"+me->query("SJ_Credit")+HIR"�뼰ʱ����ʦ��ϵ�����������Ϣ�Ѿ���¼�ڰ���\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",2000);
		log_file("quest/edittongbao", sprintf("%s(%s) ��ʱ��ͨ��Ϊ%d����˫�����飺%d����ǰ���飺%d��VIP���Ϊ%s��\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );

	}

*/                                      
	
}
