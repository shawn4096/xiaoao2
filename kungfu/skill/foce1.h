int valid_public(object me)
{
      mapping skl = me->query_skills();
      string *sk;
      int i;
      string skl_name = explode(__FILE__, "/")[<1][0..<3];

      if (!mapp(skl)) return 1;
      sk = keys(skl);
      i = sizeof(sk);
      while (i--) {
        if (sk[i] == "jiuyang-shengong" || sk[i] == "jiuyin-zhengong" || sk[i] == "lengquan-shengong" || sk[i] == "shenzhao-jing"
        || sk[i] == "hamagong" || sk[i] == "kuihua-shengong"|| sk[i] == "taixuan-gong" || sk[i] == "xixing-dafa" || sk[i] == "beiming-shengong"
        || sk[i] == "bahuang-gong" || sk[i] == "xiaowu-xianggong" || sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong" || sk[i] == "taiji-shengong"
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong") continue;
        
        if (sk[i] != skl_name && SKILL_D(sk[i])->valid_enable("force"))
          return notify_fail("�㲻ɢ��"+to_chinese(sk[i])+"���������ϰ"+to_chinese(skl_name)+"��\n");
      }
      


      return 1;
}
int force_effect(string skill)
{	
	//�Կ�Ч���Ǵ�-3 -> 3���ֱ����������ص����˺��ᣬΨһһ�����⣬��jiuyin-zhengong������
	//��Ȼ������������Ч��
	//��ͬ�ڹ����ʵ��ڹ���������˵�Ч����dulong-dafa���������ڹ���
	//���Ե��ڹ��Կ������Ч���ͺã����������ڹ����޷��Կ�����Ҫ�����˺�
	//û���г������ڹ������������ڹ����޷������ˡ�:(
        switch (skill)
        {//���������ж�
                case "jiuyang-shengong" : return 9;
				case "hamagong"         : return 9;
                case "yijin-jing"       : return 8;
				case "longxiang-boruo"  : return 2;
                case "huntian-qigong"   : return 3;
                case "qiantian-yiyang"  : return 3;
                case "guiyuan-tunafa"   : return 3;
                case "kurong-changong"  : return 1;
                case "shenghuo-shengong": return 2;
                case "huashan-qigong"   : return 2;
                case "huntian-qigong"   : return 0;
                case "linji-zhuang"     : return -1;
                case "shenzhao-jing"    : return -1;
                case "shenyuan-gong"    : return -1;
                
                case "dulong-dafa"      : return -2;
                case "huagong-dafa"     : return -2;
                case "xuantian-wuji"    : return -4;
                case "yunu-xinjing"     : return -3;
                case "hanbing-zhenqi"   : return -3;
                case "bihai-chaosheng"  : return -3;
				case "zixia-gong"       : return -2;
				case "yinyun-ziqi"      : return -2;
				case "lengquan-shengong"  : return -4;
				case "kuihua-shengong"  : return -4;
                case "jiuyin-zhengong"  : return -4;
                default: return 1;
        }
}