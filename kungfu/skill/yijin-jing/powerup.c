// panix 01/09/14

#include <ansi.h>
void remove_effect(object me,int count);

//�����б� copy from yinyun-ziqi qudu
mapping *poi_list = ({
([
"id":		"snake_poison",	// ���ж���E������
"name":		"�߶�",		// ���ж�����������
"col":		""BLU"",	// �ж���������ɫ
"con":		"տ��֮��",	// �ж�������״̬
]), 
([
"id":		"xx_poison",
"name":		"�����ƶ�",
"col":		""BLU"",
"con":		"տ��֮��",
]),
([
"id":		"xuanmin_poison",
"name":		"��ڤ�ƶ�",
"col":		""HIW"",
"con":		"˪��֮��",
]),
([
"id":		"dsy_poison",
"name": 	"���ڴ���ӡ�ƶ�",
"col":		""CYN"",
"con":		"��ɫ֮��",
]),
([
"id":		"fs_poison",
"name":		"��ʬ��",
"col":		""HIG"",
"con":		"��ɫ֮��",
]),
([
"id":		"huagu_poison",
"name":		"�������ƾ綾",
"col":		""BLU"",
"con":		"տ��֮��",
]),
([
"id":		"man_poison",
"name":		"�����ܻ���",
"col":		""HIB"",
"con":		"��ɫ֮��",
]),
([
"id":		"qinghua_poison",
"name":		"�黨��",
"col":		""MAG"",
"con":		"��ɫ֮��",
]),
([
"id":		"qishang_poison",
"name":		"����ȭ��",
"col":		""HIR"",
"con":		"����֮��",
]),
([
"id":		"qzhu_poison",
"name":		"ǧ�����ֶ�",
"col":		""HIR"",
"con":		"����֮��",
]),
([
"id":		"sl_poison",
"name":		"������",
"col":		""BLU"",
"con":		"տ��֮��",
]),
([
"id":		"sy_poison",
"name":		"����ӡ�ƶ�",
"col":		""HIR"",
"con":		"����֮��",
]),
([
"id":		"warm_poison",
"name":		"�ȶ�",
"col":		""RED"",
"con":		"���֮��",
]),
([
"id":		"hot_poison",
"name":		"��",
"col":		""HIR"",
"con":		"����֮��",
]),
([
"id":		"cold_poison",
"name":		"����",
"col":		""HIC"",
"con":		"����֮��",
]),
([
"id":		"bing_poison",
"name":		"�������붾",
"col":		""HIB"",
"con":		"տ��֮��",
]),
([
"id":		"bt_poison",
"name":		"���߶�",
"col":		""YEL"",
"con":		"����֮��",
]),
([
"id":		"hb_poison",
"name":		"�������ƶ�",
"col":		""HIB"",
"con":		"տ��֮��",
]),
});

int exert(object me)
{    
      int improve;
	  if (me->query("yjj/powerup")!="pass") 
		  return notify_fail("��ֻ����˵���׽֮�����񹦣���ȴ������ʹ�á������񹦡���\n");
      if ( !me->is_fighting()&&(int)me->query_skill("yijin-jing", 1) < 550)
                return notify_fail("��ֻ����ս����ʹ���׽�������񹦡���\n");

      if( (int)me->query_skill("yijin-jing", 1) < 450 )
                return notify_fail("����׽�ڹ���Ϊ�������޷�ʹ�á������񹦡���\n");
				
	  if( (int)me->query_skill("buddhism", 1) < 200 )
                return notify_fail("��ķ���Ϊ�������޷�ʹ�á������񹦡���\n");

      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("����ʹ�õ��ڹ����ԣ�\n");

      if( (int)me->query_con() < 60 )
                return notify_fail("��ĸ���̫�ͣ������޷�ʹ�á������񹦡���\n");
 
      if( (int)me->query("neili") < 5000 )
                return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á������񹦡���\n");   
      if( (int)me->query_skill("medicine",1) < 120 )
                return notify_fail("��Ŀǰ�ı�������̫���ˣ��޷�ʹ�á������񹦡���\n");   
      if( (int)me->query("max_neili") < 10000 )
                return notify_fail("���������Ϊ��ô�����ʹ�á������񹦡���\n");   
                                                                                
      if( me->query_temp("yjj/powerup"))
                return notify_fail("���������á������񹦡���\n");
				
	  improve = (int)me->query_skill("yijin-jing", 1)/10;
	  if ( improve > 60 ) improve = 60 + (improve-60) / 10;
	  me->set_temp("yjj/powerup",improve);
       
      message_vision(HBRED+HIW"\n$N����Ĭ������������ࡢ���ࡢ�����ࡢ�����࣬�����������پ�������ִ���ִ����ڣ��׽��ȫ����ת������������\n" NOR, me);
      if ((int)me->query_skill("yijin-jing", 1) < 500){
          me->start_busy(random(1));
		  me->start_exert(2,"�������񹦡�");
	  }
     // me->set_temp("yjj/powerup", me->query_skill("yijin-jing", 1)/2); 
     // me->add_temp("apply/dodge", me->query_skill("yijin-jing", 1)/6); //dodge,parry �ɽ����ɣ���ղ��ط�����powerup���ع���
      //me->add_temp("apply/parry", me->query_skill("yijin-jing", 1)/6);
      me->add_temp("apply/attack", me->query_skill("yijin-jing", 1)/2);
	  me->add_temp("apply/damage", me->query_skill("yijin-jing", 1)/4);
      me->add("neili", -500);
      message_vision(HBRED+HIY"$N����ȫ�ڻ��ͨ�׽ȫ���й�������ʲôƽӹ֮�����书������������ܻ�����Ϊ���棡\n" NOR, me);
	  me->add_temp("apply/strength", improve);
	  me->add_temp("apply/constitution", improve/2);
	  me->add_temp("apply/dexerity", improve);
	  me->add("neili", -500);
	     
      call_out("remove_effect", 1, me, improve);
      return 1;
}

void remove_effect(object me,int count)
{
        int improve;
		mapping conditions,my_poison,poison;
 	    string *names,name,poison_name,poison_col,poison_con;
 	    int lvl=0;
	    int i,k;
		if (!me) return;
	    
		poison_name="δ֪��";
		poison_col=""HIB"";
		poison_con="��ɫ֮��";
		improve = (int)me->query_temp("yjj/powerup");
	   
        if( !me) return;
        if(me->query_temp("yjj/powerup")) {
            if( count < 1 ){
                me->delete_temp("yjj/powerup");             
                me->add_temp("apply/attack",-me->query_skill("yijin-jing", 1)/2);             
		    	me->add_temp("apply/damage",-me->query_skill("yijin-jing", 1)/4);
		        me->add_temp("apply/strength", -improve);
		        me->add_temp("apply/constitution", -improve/2);
		        me->add_temp("apply/dexerity", -improve);
		       //	me->delete_temp("yjj/powerup");
                message_vision(HIR"\n$N������������Ҳ����ά���������ҵĴ�����״̬��\n"NOR, me);    
                return;
            }
            else { 
		        if (me->query_temp("yjj/powerup") 
					//&& me->query("yjj/powerup")
					&&!random(2)) {
	              
					if(mapp(conditions = me->query_conditions_by_type("poison"))){
	                	names = keys(conditions);
						
	                	for(i=0;i<sizeof(conditions);i++){
						    name  = names[i];
							//������������Ӧ,�����ڱ��
							for(k=0;k<sizeof(poi_list);k++) {
	                         	if(poi_list[k]["id"]==name) {
	                         	  poison_name=poi_list[k]["name"];
							      poison_col =poi_list[k]["col"];
							      poison_con =poi_list[k]["con"];
							      break;
								  }
	                        }							
							
							//����������ж�,��ʼ�ⶾ
	                		if(conditions[names[i]]>0) {
							   message_vision(HIY"$N�����ڻ��ͨ�׽��ȫ���й���������ɫƤ����"+poison_col+poison_con+HIY+"ʱ��ʱ��,ȴ���׽��������"+poison_col+poison_name+HIY+"�Ķ��������⣡\n"NOR,me);
                               me->add_condition(name,-random((int)me->query_condition(name)));
							}
							else {
							   message_vision(HIY"$N�����ڻ��ͨ�׽��ȫ���й���������ɫƤ����"+poison_col+poison_con+HIY+"һ����û,ԭ���׽�ѽ�����"+poison_col+poison_name+HIY+"�Ķ��ʳ������⣡\n"NOR,me);
                               me->clear_condition(name);
							}
	                	} //�����ж��ض������
	                }
			    }
                call_out("remove_effect", 1, me,count -1);
                return;
            }
        }
}
string exert_name(){ return HIW"������"NOR; }

int help(object me)
{
        write(HIY"\n�׽֮�������񹦡���"NOR"\n");
        write(@HELP
        ���׽��ʵ����ѧ���������ϵı��䣬ֻ����ϰ�ķ�����Ϊ���ף���
        �ÿ��ơ����ࡢ���ࡱ�����в�����ϰ�书֮�����������ɾ��磬
        һ���ڻ��ͨ�׽ȫ���й�������ʲôƽӹ֮�����书���������
        ���ܻ�����Ϊ���棬���ҹ���ȫ���ܹ�����ٶ���
        
		Ҫ��
			�׽�ȼ� 450 ���ϣ�
			�����ķ��ȼ� 200 ��
			���� 60 ���ϣ�
			������� 10000 ���ϣ�
			���� 5000 ���ϡ�
HELP
        );
        return 1;
}
