package dico;

public interface IDictionary 
{
	Object get(Object key);
	void put(Object key,Object value);
	boolean isEmpty();
	boolean containsKey(Object key);
}
