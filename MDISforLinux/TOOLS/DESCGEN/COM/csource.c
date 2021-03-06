/*********************  P r o g r a m  -  M o d u l e ***********************
 *
 *         Name: csource.c
 *      Project: descgen
 *
 *       Author:
 *
 *  Description: Output descriptor as C-source
 *
 *
 *     Required:
 *     Switches:
 *
 *---------------------------[ Public Functions ]----------------------------
 *
 *
 *---------------------------------------------------------------------------
 * Copyright 1997-2019, MEN Mikro Elektronik GmbH
 ******************************************************************************/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <MEN/men_typs.h>
#include <MEN/desctyps.h>
#include "descgen.h"

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/

/*--------------------------------------+
|   TYPDEFS                             |
+--------------------------------------*/

/*--------------------------------------+
|   EXTERNALS                           |
+--------------------------------------*/

/*--------------------------------------+
|   GLOBALS                             |
+--------------------------------------*/

/*--------------------------------------+
|   PROTOTYPES                          |
+--------------------------------------*/
void OutCStruct( FILE *fp, DESCR_TAG *topTag, int32 level );
void OutCValues( FILE *fp, DESCR_TAG *topTag, int32 level );
void Indent(FILE *fp, int32 level);

/********************************* OutCSource *******************************
 *
 *  Description: Output internal data base as C-source code
 *
 *
 *---------------------------------------------------------------------------
 *  Input......: fname			output filename for source file
 *				 topTag			root directory of objects
 *  Output.....: error code
 *  Globals....: -
 ****************************************************************************/
int32 OutCSource( char *fname, DESCR_TAG *topTag )
{
	FILE *fp;
	DESCR_TAG *tag;
	char cfile[MAX_FNAME_LENGTH], *p;
	char fbody[MAX_FNAME_LENGTH];
	time_t ltime;

	time(&ltime);

	/*-------------------+
	|  create file name  |
	+-------------------*/
	/* remove file extension */
	strcpy( fbody, fname );
	if( (p = strrchr( fbody, '.' )))
		*p = '\0';

	sprintf(cfile,"%s%c%s.c",G_outputDir,MEN_PATHSEP,fbody);

	/*-------------------+
	|  check if output   |
	|  file already exist|
	+-------------------*/
	if (FileExist(cfile))
		if (!G_overwrite) {
			fprintf(stderr,"*** output file %s already exists\n",
					cfile);
			return(1);
		}
		else
			printf("overwriting %s\n",cfile);
	else
		printf("creating %s\n",cfile);

	/*-------------------+
    |  Open output file  |
    +-------------------*/
	if( (fp = fopen( cfile, "w" )) == NULL ){
		fprintf( stderr, "*** error %d opening output file %s\n",
				errno, cfile );
		return errno;
	}

	fprintf( fp, "/*\n * Generated by descgen %s (MDIS descriptor generator)\n", G_version);
	fprintf( fp, " * %s", ctime(&ltime));
	fprintf( fp, " * You can edit this file on your own risk. You should\n");
	fprintf( fp, " * better edit the descgen input file\n */\n\n");

	/*--- fill in include files ---*/
	fprintf( fp, "#include <MEN/men_typs.h>\n");
	fprintf( fp, "#include <MEN/desctyps.h>\n");

	/*--------------------------------+
    |  Output C-structure definitions |
    +--------------------------------*/
	for( tag=topTag->children; tag; tag=tag->next ){

		/*-----------------------------------+
        |  generate C-structure declaration  |
        +-----------------------------------*/

		fprintf( fp, "\n/*==== Descriptor for \"%s\" ====*/\n", tag->name );
		Indent(fp, 0 );
		fprintf( fp, "struct {\n");

		OutCStruct( fp, tag, 1 );

		Indent(fp, 1 );
		fprintf( fp, "struct {\n" );
		Indent(fp, 2 );
		fprintf( fp, "u_int16 __typ, __len;\n" );
		Indent(fp, 1 );
		fprintf( fp, "} __end_%s;\n", tag->name );

		Indent( fp, 0 );
		fprintf( fp, "} %s = {\n", tag->name);


		/*--------------------+
        |  Fill with values   |
        +--------------------*/
		OutCValues( fp, tag, 1 );

		Indent( fp, 1 );
		fprintf( fp, "{ DESC_%s, 0 }\n", TagTypeName(DESC_END));
		fprintf( fp, "};\n");
	}

	fclose(fp);
	return(0);
}

/********************************* OutCStruct ********************************
 *
 *  Description: Output C-structure for a single tag directory
 *
 *
 *---------------------------------------------------------------------------
 *  Input......: fp			outfile stream
 *				 topTag		tag to generate
 *				 level		recursion level
 *  Output.....: -
 *  Globals....: -
 ****************************************************************************/
void OutCStruct( FILE *fp, DESCR_TAG *topTag, int32 level )
{
	DESCR_TAG *tag;

	for( tag=topTag->children; tag; tag=tag->next ){
		switch( tag->type ){
		case DESC_DIR:
			fprintf( fp, "\n");
			Indent(fp, level );
			fprintf( fp, "/*--- directory %s ---*/\n", tag->name );

			Indent(fp, level );
			fprintf( fp, "struct {\n" );

			Indent(fp, level+1 );
			fprintf( fp, "struct {\n" );

			Indent(fp, level+2 );
			fprintf( fp, "u_int16 __typ, __len; char __name[%d];\n",
					strlen(tag->name) + 1 + tag->align1 );

			Indent(fp, level+1 );
			fprintf( fp, "} __%s;\n", tag->name );


			OutCStruct( fp, tag, level+1 );

			/*--- end tag ---*/
			Indent(fp, level+1 );
			fprintf( fp, "struct {\n" );
			Indent(fp, level+2 );
			fprintf( fp, "u_int16 __typ, __len;\n" );
			Indent(fp, level+1 );
			fprintf( fp, "} __end_%s;\n", tag->name );

			Indent(fp, level );
			fprintf( fp, "} %s;\n", tag->name );
			break;

		case DESC_U_INT32:
		case DESC_BINARY:
		case DESC_STRING:
			Indent(fp, level );
			fprintf( fp, "struct {  /* %s */\n", tag->name);

			Indent(fp, level+1 );

			fprintf( fp, "u_int16 __typ, __len; char __name[%d];\n",
					strlen(tag->name) + 1 + tag->align1 );

			Indent(fp, level+1 );

			switch( tag->type ){
			case DESC_U_INT32:
				fprintf(fp, "u_int32 val;\n" );
				break;

			case DESC_BINARY:
				fprintf( fp, "u_int8 __val[%d];\n",
						tag->val.uInt8.entries + tag->align2 + 1);
				break;

			case DESC_STRING:
				fprintf( fp, "char __val[%d];\n",
						strlen(tag->val.string) + 1 + tag->align2 );
				break;
			}

			Indent(fp, level );
			fprintf( fp, "} %s;\n", tag->name );
			break;
		}
	}
}

/********************************* OutCValues ********************************
 *
 *  Description: Output C-values for a single tag directory
 *
 *
 *---------------------------------------------------------------------------
 *  Input......: fp			outfile stream
 *				 topTag		tag to generate
 *				 level		recursion level
 *  Output.....: -
 *  Globals....: -
 ****************************************************************************/
void OutCValues( FILE *fp, DESCR_TAG *topTag, int32 level )
{
	DESCR_TAG *tag;
	int i;

	for( tag=topTag->children; tag; tag=tag->next ){

		if( tag->type == DESC_DIR ){
			Indent(fp, level );
			fprintf( fp, "{\n" );
			level++;
		}

		Indent(fp, level );
		fprintf( fp, "{ " );

		fprintf( fp, "DESC_%s, %d, \"%s\"", TagTypeName(tag->type),
				tag->len, tag->name );


		switch( tag->type ){
		case DESC_DIR:
			fprintf(fp, " },\n" );
			OutCValues( fp, tag, level );

			Indent(fp, level );
			fprintf( fp, "{ DESC_%s, 0 }\n", TagTypeName(DESC_END));

			level--;
			Indent(fp, level );
			fprintf(fp, "}");
			break;

		case DESC_U_INT32:
			fprintf(fp, ", 0x%08x }", tag->val.uInt32 );
			break;

		case DESC_BINARY:
			fprintf( fp, ",\n" );
			Indent(fp, level+1 );
			fprintf( fp, "{ " );
			fprintf( fp, "%d /*PF*/,", tag->align2 );
			for( i=0; i<tag->val.uInt8.entries; i++ ){
				fprintf( fp, "0x%02x%s", tag->val.uInt8.arr[i],
						i==tag->val.uInt8.entries-1 ? "" : "," );
			}
			fprintf( fp, " }\n" );
			Indent(fp, level   );
			fprintf( fp, "}" );
			break;

		case DESC_STRING:
			fprintf( fp, ", \"%s\" }", tag->val.string );
			break;
		}

		/*if( (tag->next == NULL) && (level==1) )
			fprintf(fp,"\n");
		else*/
			fprintf(fp,",\n");

	}
}


/********************************* Indent ***********************************
 *
 *  Description: Line indention
 *
 *
 *---------------------------------------------------------------------------
 *  Input......:
 *  Output.....:
 *  Globals....: -
 ****************************************************************************/
void Indent( FILE *fp, int32 level)
{
	fprintf( fp, "%*s", level*4, "" );
}

