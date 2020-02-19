package com.ec.constants;

import com.sun.jna.Pointer;
import com.sun.jna.Structure;

public class EC_Constant {
	
	public static final int DECRYPT_M = 0;
	public static final int DECRYPT_MN = 1;
	public static final int PNUM_SIZE = 7;
	public static final int SECURITY_LOOP = 10;
	
	public static Pointer primeNumberExpo_t;

	public static class KeyValuePair extends Structure{
		public Pointer primeNumberExpo_t;
		public int value;
	}
}
