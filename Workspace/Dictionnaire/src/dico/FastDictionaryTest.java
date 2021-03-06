package dico;

import static org.junit.Assert.*;
import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import dico.FastDictionary;

@RunWith(Parameterized.class)
public class FastDictionaryTest 
{
	public FastDictionary dico=new FastDictionary(10);
	public Object p_key;
	public Object p_value;
	
	@Parameters
	public static Collection<Object[]> testData()
	{
		return Arrays.asList(new Object [][]
		{
			{"dark","the absence of light"},//jeu de tests
			{"God","the creator and ruler of the universe"},
			{"read","look at and comprehend the meaning "}
		});
	}
	
	public FastDictionaryTest(Object key,Object val) 
	{
		p_key=key;//initialisation des cl�s et valeurs � la vol�e
		p_value=val;
	}
	
	@Test
	public void add_access()
	{
		dico.put(p_key, p_value);
		assertEquals(p_value,dico.get(p_key));
	}
	
	@Test
	public void testNewIndex()
	{
		System.out.println(dico.newIndexOf(p_key));
	}
	
	@Test
	public void testIndexOf()
	{
		System.out.println(dico.indexOf(p_key));
	}
}
