#include "nr_micro_shell.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "qcbor/qcbor_encode.h"
#include "qcbor/qcbor_decode.h"
#include "qcbor/qcbor_spiffy_decode.h"
#include "UsefulBuf.h"

/**
 * This is a simple example of encoding and decoding some CBOR from
 * and to a C structure.
 *
 * This also includes a comparison between the original structure
 * and the one decoded from the CBOR to confirm correctness.
 */


#define MAX_CYLINDERS 16

/**
 * The data structure representing a car engine that is encoded and
 * decoded in this example.
 */
typedef struct
{
   UsefulBufC Manufacturer;
   int64_t    uDisplacement;
   int64_t    uHorsePower;
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
   double     dDesignedCompresion;
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
   int64_t    uNumCylinders;
   bool       bTurboCharged;
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
   struct {
      double dMeasuredCompression;
   } cylinders[MAX_CYLINDERS];
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
} CarEngine;

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')

void dump_hex(const uint8_t *buf, uint32_t size, uint32_t number)
{
    int i, j;
    char buffer[128] = {0};
    int n = 0;

    for (i = 0; i < size; i += number)
    {
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%08X: ", i);

        for (j = 0; j < number; j++)
        {
            if (j % 8 == 0)
            {
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, " ");
            }
            if (i + j < size)
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%02X ", buf[i + j]);
            else
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "   ");
        }
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, " ");

        for (j = 0; j < number; j++)
        {
            if (i + j < size)
            {
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, "\n");
        printf("%s", buffer);
        n = 0;
        memset(buffer, 0, sizeof(buffer));
    }
}


/**
 * @brief Initialize the Engine data structure with values to encode.
 *
 * @param[out] pE   The Engine structure to fill in
 */
void EngineInit(CarEngine *pE)
{
   pE->Manufacturer        = UsefulBuf_FROM_SZ_LITERAL("Porsche");
   pE->uDisplacement       = 3296;
   pE->uHorsePower         = 210;
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
   pE->dDesignedCompresion = 9.1;
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
   pE->uNumCylinders       = 6;
   pE->bTurboCharged       = false;

#ifndef USEFULBUF_DISABLE_ALL_FLOAT
   pE->cylinders[0].dMeasuredCompression = 9.0;
   pE->cylinders[1].dMeasuredCompression = 9.2;
   pE->cylinders[2].dMeasuredCompression = 8.9;
   pE->cylinders[3].dMeasuredCompression = 8.9;
   pE->cylinders[4].dMeasuredCompression = 9.1;
   pE->cylinders[5].dMeasuredCompression = 9.0;
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
}


/**
 * @brief Compare two Engine structure for equality.
 *
 * @param[in] pE1  First Engine to compare.
 * @param[in] pE2  Second Engine to compare.
 *
 * @retval Return @c true if the two Engine data structures are exactly the
 *         same.
 */
static bool EngineCompare(const CarEngine *pE1, const CarEngine *pE2)
{
   if(pE1->uNumCylinders != pE2->uNumCylinders) {
      return false;
   }
   if(pE1->bTurboCharged != pE2->bTurboCharged) {
      return false;
   }
   if(pE1->uDisplacement != pE2->uDisplacement) {
      return false;
   }
   if(pE1->uHorsePower != pE2->uHorsePower) {
      return false;
   }
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
   if(pE1->dDesignedCompresion != pE2->dDesignedCompresion) {
      return false;
   }
   for(int64_t i = 0; i < pE2->uNumCylinders; i++) {
      if(pE1->cylinders[i].dMeasuredCompression !=
         pE2->cylinders[i].dMeasuredCompression) {
         return false;
      }
   }
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */

   if(UsefulBuf_Compare(pE1->Manufacturer, pE2->Manufacturer)) {
      return false;
   }

    return true;
}


/**
 * @brief Encode an initialized CarEngine data structure in CBOR.
 *
 * @param[in] pEngine  The data structure to encode.
 * @param[in] Buffer   Pointer and length of buffer to output to.
 *
 * @return  The pointer and length of the encoded CBOR or
 *          @ref NULLUsefulBufC on error.
 *
 * This encodes the input structure \c pEngine as a CBOR map of
 * label-value pairs. An array of float is one of the items in the
 * map.
 *
 * This uses the UsefulBuf convention of passing in a non-const empty
 * buffer to be filled in and returning a filled in const buffer. The
 * buffer to write into is given as a pointer and length in a
 * UsefulBuf. The buffer returned with the encoded CBOR is a
 * UsefulBufC also a pointer and length. In this implementation the
 * pointer to the returned data is exactly the same as that of the
 * empty buffer. The returned length will be smaller than or equal to
 * that of the empty buffer. This gives correct const-ness for the
 * buffer passed in and the data returned.
 *
 * @c Buffer must be big enough to hold the output. If it is not @ref
 * NULLUsefulBufC will be returned. @ref NULLUsefulBufC will be
 * returned for any other encoding errors.
 *
 * This can be called with @c Buffer set to @ref SizeCalculateUsefulBuf
 * in which case the size of the encoded engine will be calculated,
 * but no actual encoded CBOR will be output. The calculated size is
 * in @c .len of the returned @ref UsefulBufC.
 */
UsefulBufC EncodeEngine(const CarEngine *pEngine, UsefulBuf Buffer)
{
   /* Set up the encoding context with the output buffer */
    QCBOREncodeContext EncodeCtx;
    QCBOREncode_Init(&EncodeCtx, Buffer);

    /* Proceed to output all the items, letting the internal error
     * tracking do its work */
    QCBOREncode_OpenMap(&EncodeCtx);
    QCBOREncode_AddTextToMap(&EncodeCtx, "Manufacturer", pEngine->Manufacturer);
    QCBOREncode_AddInt64ToMap(&EncodeCtx, "NumCylinders", pEngine->uNumCylinders);
    QCBOREncode_AddInt64ToMap(&EncodeCtx, "Displacement", pEngine->uDisplacement);
    QCBOREncode_AddInt64ToMap(&EncodeCtx, "Horsepower", pEngine->uHorsePower);
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
    QCBOREncode_AddDoubleToMap(&EncodeCtx, "DesignedCompression", pEngine->dDesignedCompresion);
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
    QCBOREncode_OpenArrayInMap(&EncodeCtx, "Cylinders");
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
    for(int64_t i = 0 ; i < pEngine->uNumCylinders; i++) {
        QCBOREncode_AddDouble(&EncodeCtx,
                              pEngine->cylinders[i].dMeasuredCompression);
    }
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
    QCBOREncode_CloseArray(&EncodeCtx);
    QCBOREncode_AddBoolToMap(&EncodeCtx, "Turbo", pEngine->bTurboCharged);
    QCBOREncode_CloseMap(&EncodeCtx);

    /* Get the pointer and length of the encoded output. If there was
     * any encoding error, it will be returned here */
    UsefulBufC EncodedCBOR;
    QCBORError uErr;
    uErr = QCBOREncode_Finish(&EncodeCtx, &EncodedCBOR);
    if(uErr != QCBOR_SUCCESS) {
       return NULLUsefulBufC;
    } else {
       return EncodedCBOR;
    }
}


/**
 * Error results when decoding an Engine data structure.
 */
typedef enum  {
    EngineSuccess,
    CBORNotWellFormed,
    TooManyCylinders,
    EngineProtocolerror,
    WrongNumberOfCylinders
} EngineDecodeErrors;


/**
 * Convert @ref QCBORError to @ref EngineDecodeErrors.
 */
static EngineDecodeErrors ConvertError(QCBORError uErr)
{
    EngineDecodeErrors uReturn;

    switch(uErr)
    {
        case QCBOR_SUCCESS:
            uReturn = EngineSuccess;
            break;

        case QCBOR_ERR_HIT_END:
            uReturn = CBORNotWellFormed;
            break;

        default:
            uReturn = EngineProtocolerror;
            break;
    }

    return uReturn;
}


/**
 * @brief Simplest engine decode using spiffy decode features.
 *
 * @param[in] EncodedEngine  Pointer and length of CBOR-encoded engine.
 * @param[out] pE            The structure filled in from the decoding.
 *
 * @return The decode error or success.
 *
 * This decodes the CBOR into the engine structure.
 *
 * As QCBOR automatically supports both definite and indefinite maps
 * and arrays, this will decode either.
 *
 * This uses QCBOR's spiffy decode functions, so the implementation is
 * simple and closely parallels the encode implementation in
 * EncodeEngineDefiniteLength().
 *
 * Another way to decode without using spiffy decode functions is to
 * use QCBORDecode_GetNext() to traverse the whole tree.  This
 * requires a more complex implementation, but is faster and will pull
 * in less code from the CBOR library. The speed advantage is likely
 * of consequence when decoding much much larger CBOR on slow small
 * CPUs.
 *
 * A middle way is to use the spiffy decode
 * QCBORDecode_GetItemsInMap().  The implementation has middle
 * complexity and uses less CPU.
 */
EngineDecodeErrors DecodeEngineSpiffy(UsefulBufC EncodedEngine, CarEngine *pE)
{
    QCBORError         uErr;
    QCBORDecodeContext DecodeCtx;

    /* Let QCBORDecode internal error tracking do its work. */
    QCBORDecode_Init(&DecodeCtx, EncodedEngine, QCBOR_DECODE_MODE_NORMAL);
    QCBORDecode_EnterMap(&DecodeCtx, NULL);
    QCBORDecode_GetTextStringInMapSZ(&DecodeCtx, "Manufacturer", &(pE->Manufacturer));
    QCBORDecode_GetInt64InMapSZ(&DecodeCtx, "Displacement", &(pE->uDisplacement));
    QCBORDecode_GetInt64InMapSZ(&DecodeCtx, "Horsepower", &(pE->uHorsePower));
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
    QCBORDecode_GetDoubleInMapSZ(&DecodeCtx, "DesignedCompression", &(pE->dDesignedCompresion));
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
    QCBORDecode_GetBoolInMapSZ(&DecodeCtx, "Turbo", &(pE->bTurboCharged));

    QCBORDecode_GetInt64InMapSZ(&DecodeCtx, "NumCylinders", &(pE->uNumCylinders));

    /* Check the internal tracked error now before going on to
     * reference any of the decoded data, particularly
     * pE->uNumCylinders */
    uErr = QCBORDecode_GetError(&DecodeCtx);
    if(uErr != QCBOR_SUCCESS) {
        goto Done;
    }

    if(pE->uNumCylinders > MAX_CYLINDERS) {
        return TooManyCylinders;
    }

    QCBORDecode_EnterArrayFromMapSZ(&DecodeCtx, "Cylinders");
#ifndef USEFULBUF_DISABLE_ALL_FLOAT
    for(int64_t i = 0; i < pE->uNumCylinders; i++) {
        QCBORDecode_GetDouble(&DecodeCtx,
                              &(pE->cylinders[i].dMeasuredCompression));
    }
#endif /* USEFULBUF_DISABLE_ALL_FLOAT */
    QCBORDecode_ExitArray(&DecodeCtx);
    QCBORDecode_ExitMap(&DecodeCtx);

    /* Catch further decoding error here */
    uErr = QCBORDecode_Finish(&DecodeCtx);

Done:
    return ConvertError(uErr);
}


int32_t RunQCborExample(void)
{
   CarEngine                 InitialEngine;
   CarEngine                 DecodedEngine;

   /* For every buffer used by QCBOR a pointer and a length are always
    * carried in a UsefulBuf. This is a secure coding and hygene
    * practice to help make sure code never runs off the end of a
    * buffer.
    *
    * UsefulBuf structures are passed as a stack parameter to make the
    * code prettier. The object code generated isn't much different
    * from passing a pointer parameter and a length parameter.
    *
    * This macro is equivalent to:
    *    uint8_t    __pBufEngineBuffer[300];
    *    UsefulBuf  EngineBuffer = {__pBufEngineBuffer, 300};
    */
   UsefulBuf_MAKE_STACK_UB(  EngineBuffer, 300);

   /* The pointer in UsefulBuf is not const and used for representing
    * a buffer to be written to. For UsefulbufC, the pointer is const
    * and is used to represent a buffer that has been written to.
    */
   UsefulBufC                EncodedEngine;
   EngineDecodeErrors        uErr;

   /* Initialize the structure with some values. */
   EngineInit(&InitialEngine);

   /* Encode the engine structure. */
   EncodedEngine = EncodeEngine(&InitialEngine, EngineBuffer);
   if(UsefulBuf_IsNULLC(EncodedEngine)) {
      printf("Engine encode failed\n");
      goto Done;
   }
   printf("Example: Definite Length Engine Encoded in %u bytes\n",
          EncodedEngine.len);

    dump_hex(EncodedEngine.ptr, EncodedEngine.len, 16);

   /* Decode the CBOR */
   uErr = DecodeEngineSpiffy(EncodedEngine, &DecodedEngine);
   printf("Example: Spiffy Engine Decode Result: %d\n", uErr);
   if(uErr) {
      goto Done;
   }

   /* Check the results */
   if(!EngineCompare(&InitialEngine, &DecodedEngine)) {
      printf("Example: Spiffy Engine Decode comparison fail\n");
   }


   /* Further example of how to calculate the encoded size, then allocate */
   UsefulBufC EncodedEngineSize;
   EncodedEngineSize = EncodeEngine(&InitialEngine, SizeCalculateUsefulBuf);
   if(UsefulBuf_IsNULLC(EncodedEngine)) {
      printf("Engine encode size calculation failed\n");
      goto Done;
   }
   (void)EncodedEngineSize; /* Supress unsed variable warning */
   /* Here malloc could be called to allocate a buffer. Then
    * EncodeEngine() can be called a second time to actually
    * encode. (The actual code is not live here to avoid a
    * dependency on malloc()).
    *  UsefulBuf  MallocedBuffer;
    *  MallocedBuffer.len = EncodedEngineSize.len;
    *  MallocedBuffer.ptr = malloc(EncodedEngineSize.len);
    *  EncodedEngine = EncodeEngine(&InitialEngine, MallocedBuffer);
    */

Done:
   printf("\n");

   return 0;
}

/*
 * A considerable number of the security issues with C code come from
 * mistakes made with pointers and lengths.  UsefulBuf adopts a
 * convention that a pointer and length *always* go together to help
 * mitigate this.  With UsefulBuf there are never pointers without
 * lengths, so you always know how big a buffer or some binary data
 * is.
 *
 * C99 allows passing structures so a structure is used. Compilers are
 * smart these days so the object code produced is little different
 * than passing two separate parameters. Passing structures also makes
 * the interfaces prettier. Assignments of structures also can make
 * code prettier.
 *
 * ALong with the UsefulBuf structure, there are a bunch of (tested!)
 * functions to manipulate them so code using it may have no pointer
 * manipulation at all.
 *
 * Constness is also a useful and desirous thing. See
 * https://stackoverflow.com/questions/117293/use-of-const-for-function-parameters
 * Keeping const distinct from non-const is helpful when reading the
 * code and helps avoid some coding mistakes.  In this example the
 * buffers filled in with data are const and the ones that are
 * to-be-filled in are not const.
 *
 * This contrived example copies data from input to output expanding
 * bytes with the value 'x' to 'xx'.
 *
 * Input -- This is the pointer and length of the input, the bytes to
 * copy. Note that UsefulBufC.ptr is a const void * indicating that
 * input data won't be changed by this function.  There is a "C" in
 * "UsefulBufC "to indicate the value is const.  The length here is
 * the length of the valid input data. Note also that the parameter
 * Input is const, so this is fully const and clearly an [in]
 * parameter.
 *
 * OutputBuffer -- This is a pointer and length of the memory to be
 * used to store the output. The correct length here is critical for
 * code security. Note that UsefulBuf.ptr is void *, it is not const
 * indicating data can be written to it. Note that the parameter
 * itself *is* const indicating that the code below will not point
 * this to some other buffer or change the length and clearly marking
 * it as an [in] parameter.
 *
 * Output -- This is the interesting and unusual one. To stay
 * consistent with always pairing a length and a pointer, this is
 * returned as a UsefulBuC. Also, to stay consistent with valid data
 * being const, it is a UsefulBufC, not a UsefulBuf. It is however, an
 * [out] parameter so the parameter is a pointer to a UsefulBufC.
 *
 * In this case and most cases, the pointer in Output->ptr will be the
 * same as OutputBuffer.ptr. This may seem redundant, but there are a
 * few reasons for it. First, is the goal of always pairing a pointer
 * and a length.  Second is being more strict and correct with
 * constness. Third is the code hygiene and clarity of having
 * variables for to-be-filled buffers be distinct from those
 * containing valid data. Fourth, there are no [in,out] parameters,
 * only [in] parameters and [out] parameters (the to-be-filled-in
 * buffer is considered an [in] parameter).
 *
 * Note that the compiler will be smart and should generate pretty
 * much the same code as for a traditional interface. On x86 with
 * gcc-11 and no stack guards, the UB code is 81 bytes and the
 * traditional code is 77 bytes.
 *
 * Finally, this supports computing of the length of the would-be
 * output without actually doing any outputting. Pass {NULL, SIZE_MAX}
 * for the OutputBuffer and the length will be returned in Output.
 */
int
ExpandxUB(const UsefulBufC   Input,
          const UsefulBuf    OutputBuffer,
          UsefulBufC        *Output)
{
    size_t uInputPosition;
    size_t uOutputPosition;

    uOutputPosition = 0;

    /* Loop over all the bytes in Input */
    for(uInputPosition = 0; uInputPosition < Input.len; uInputPosition++) {
        const uint8_t uInputByte = ((const uint8_t*)Input.ptr)[uInputPosition];

        /* Copy every byte */
        if(OutputBuffer.ptr != NULL) {
            ((uint8_t *)OutputBuffer.ptr)[uOutputPosition] = uInputByte;
        }
        uOutputPosition++;
        if(uOutputPosition >= OutputBuffer.len) {
            return -1;
        }

        /* Double output 'x' because that is what this contrived example does */
        if(uInputByte== 'x') {
            if(OutputBuffer.ptr != NULL) {
                ((uint8_t *)OutputBuffer.ptr)[uOutputPosition] = 'x';
            }
            uOutputPosition++;
            if(uOutputPosition >= OutputBuffer.len) {
                return -1;
            }
        }
    }

    *Output = (UsefulBufC){OutputBuffer.ptr, uOutputPosition};

    return 0; /* success */
}


/* This is the more tradional way to implement this. */
int
ExpandxTraditional(const uint8_t  *pInputPointer,
                   const size_t    uInputLength,
                   uint8_t        *pOutputBuffer,
                   const size_t    uOutputBufferLength,
                   size_t         *puOutputLength)
{
    size_t uInputPosition;
    size_t uOutputPosition;

    uOutputPosition = 0;

    /* Loop over all the bytes in Input */
    for(uInputPosition = 0; uInputPosition < uInputLength; uInputPosition++) {
        const uint8_t uInputByte = ((const uint8_t*)pInputPointer)[uInputPosition];

        /* Copy every byte */
        if(pOutputBuffer != NULL) {
            ((uint8_t *)pOutputBuffer)[uOutputPosition] = uInputByte;
        }
        uOutputPosition++;
        if(uOutputPosition >= uOutputBufferLength) {
            return -1;
        }

        /* Double output 'x' because that is what this contrived example does */
        if(uInputByte== 'x') {
            if(pOutputBuffer != NULL) {
                ((uint8_t *)pOutputBuffer)[uOutputPosition] = 'x';
            }
            uOutputPosition++;
            if(uOutputPosition >= uOutputBufferLength) {
                return -1;
            }
        }
    }

   *puOutputLength = uOutputPosition;

    return 0; /* success */
}


/*
 * Here's an example of going from a traditional interface
 * interface to a UsefulBuf interface.
 */
int
ExpandxTraditionalAdaptor(const uint8_t  *pInputPointer,
                          size_t          uInputLength,
                          uint8_t        *pOutputBuffer,
                          size_t          uOutputBufferLength,
                          size_t         *puOutputLength)
{
    UsefulBufC  Input;
    UsefulBuf   OutputBuffer;
    UsefulBufC  Output;
    int         nReturn;

    Input = (UsefulBufC){pInputPointer, uInputLength};
    OutputBuffer = (UsefulBuf){pOutputBuffer, uOutputBufferLength};

    nReturn = ExpandxUB(Input, OutputBuffer, &Output);

    *puOutputLength = Output.len;

    return nReturn;
}


/* Here's an example for going from a UsefulBuf interface
 to a traditional interface. */
int
ExpandxUBAdaptor(const UsefulBufC   Input,
                 const UsefulBuf    OutputBuffer,
                 UsefulBufC        *Output)
{
   Output->ptr = OutputBuffer.ptr;

   return ExpandxTraditional(Input.ptr, Input.len,
                             OutputBuffer.ptr, OutputBuffer.len,
                           &(Output->len));
}



#define INPUT "xyz123xyz"

int32_t RunUsefulBufExample(void)
{
   /* ------------ UsefulBuf examples ------------- */
   UsefulBufC Input = UsefulBuf_FROM_SZ_LITERAL(INPUT);

   /* This macros makes a 20 byte buffer on the stack. It also makes
    * a UsefulBuf on the stack. It sets up the UsefulBuf to point to
    * the 20 byte buffer and sets it's length to 20 bytes. This
    * is the empty, to-be-filled in memory for the output. It is not
    * const. */
   MakeUsefulBufOnStack(OutBuf, sizeof(INPUT) * 2);

   /* This is were the pointer and the length of the completed output
    * will be placed. Output.ptr is a pointer to const bytes. */
   UsefulBufC           Output;

   ExpandxUB(Input, OutBuf, &Output);

   ExpandxUBAdaptor(Input, OutBuf, &Output);



   /* ------ Get Size example  -------- */
   ExpandxUB(Input, (UsefulBuf){NULL, SIZE_MAX}, &Output);

   /* Size is in Output.len */



   /* ---------- Traditional examples (for comparison) --------- */
   uint8_t puBuffer[sizeof(INPUT) * 2];
   size_t  uOutputSize;

   ExpandxTraditional((const uint8_t *)INPUT, sizeof(INPUT),
                     puBuffer, sizeof(puBuffer),
                     &uOutputSize);


   ExpandxTraditionalAdaptor((const uint8_t *)INPUT, sizeof(INPUT),
                            puBuffer, sizeof(puBuffer),
                           &uOutputSize);

   return 0;
}

/**
 * @brief cbor test command
 */
void shell_cbor_cmd(int argc, char *argv)
{
   RunQCborExample();
   RunUsefulBufExample();
}
