//
//  ToastOngateProduct.h
//  ToastOngate
//
//  Created by NHNEnt on 21/01/2019.
//  Copyright © 2019 NHNEnt. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const ToastOngateDefaultUserChannel;
extern NSString *const ToastOngateDefaultCurrency;
extern NSString *const ToastOngateDefaultPrice;

/**
 # ToastOngateProduct
 
 The information of product.
 */
@interface ToastOngateProduct : NSObject

/** The identifier of product. */
@property (nonatomic, copy) NSString *productIdentifier;

/** The sequence of product. */
@property (nonatomic, assign) long productSeq;

/** The name of product. */
@property (nonatomic, copy, nullable) NSString *productName;

/** The price of product. */
@property (nonatomic, copy, nullable) NSDecimalNumber *price;

/** The currency of product. */
@property (nonatomic, copy, nullable) NSString *currency;

/** The localized price of product. */
@property (nonatomic, copy, nullable) NSString *localizedPrice;

/** If 'YES', the product is currently active. If 'NO', it is deactive. */
@property (nonatomic, assign) BOOL active;

- (instancetype)initWithProductIdentifier:(NSString *)productIdentifier
                               productSeq:(NSNumber *)productSeq
                              productName:(NSString *)productName
                              usingStatus:(NSString *)usingStatus
                                    price:(NSDecimalNumber *)price
                                 currency:(NSString *)currency;

+ (instancetype)productIdentifier:(NSString *)productIdentifier
                       productSeq:(NSNumber *)productSeq
                      productName:(NSString *)productName
                      usingStatus:(NSString *)usingStatus
                            price:(NSDecimalNumber *)price
                         currency:(NSString *)currency;

@end

NS_ASSUME_NONNULL_END
