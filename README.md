# Stripe Checkout

**This module is no longer maintained. Stripe development is now centering around
the [Stripe](https://github.com/backdrop-contrib/stripe) module, including the 
bundled `webform_stripe` functionality.**

This module enables the creation of a simple donation block
which you can place in layouts on your Backdrop site. It is a very simple
implementation using Stripe's [Checkout](https://stripe.com/docs/checkout) 
functionality and does not create local database tables for storing or 
browsing donation history. You can use your Stripe account to view and 
manage that. 

Even though Stripe handles all the payment info on their servers, you 
should still ensure your site is running on SSL. ("All submissions of payment 
info using Checkout are made via a secure HTTPS connection. However, in order 
to protect yourself from certain forms of man-in-the-middle attacks, you must 
serve the page containing the payment form over HTTPS as well. In short, the 
address of the page containing Checkout must start with https:// rather than 
just http://.")

## Features

1. *Basic Stripe Checkout donation block*: The main stripe_checkout module
  allows you to activate a simple donation block using Stripe Checkout.
2. *Stripe Checkout Webform*: The optional submodule allows you to add "Stripe
  payment" components to your webforms, so that submissions can be "purchased".

  With this, you can use webforms for event registrations, online donations, or
  even for simple products where you need to gather additional information from 
  a user. Each webform can have fixed pricing, or it can be determined 
  dynamically from another field component on the form. You can also select
  "Plans" (subscriptions) from your Stripe account to allow recurring payments.

## Dependencies

- [Stripe API](https://github.com/backdrop-contrib/stripe_api)
- [Webform](https://backdropcms.org/project/webform) 
  *for `stripe_checkout_webform` submodule only.*

## Installation

- Once the dependencies are in place, install this module using the [official 
  Backdrop CMS instructions](https://backdropcms.org/guide/modules).
- Configure the module at *Configuration > Web Services > Stripe >  
  Checkout Settings* (`admin/config/services/stripe_api/checkout`).
- Activate the "Stripe Checkout Donation" block 
  [to a layout](https://backdropcms.org/guide/layouts) and adjust visibility 
  settings as needed.
- Enable the `Stripe Checkout Webform` sub-module if you would like to be
  able to add Stripe payment fields to your webforms.

![Stripe Checkout](https://github.com/backdrop-contrib/stripe_checkout/blob/1.x-1.x/images/stripe_checkout-screenshot.jpg "Stripe Checkout screenshot")

## Issues

Bugs and Feature requests should be reported in this module's 
[Issue Queue](https://github.com/backdrop-contrib/stripe_checkout/issues).

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

## Current Maintainers

- Unmaintained

## Credits

- This module was created by [Laryn Kragt Bakker](https://github.com/laryn) - 
  [CEDC.org](https://cedc.org).
- The `stripe_checkout_webform` submodule has been included based on the 
  `webform_stripe` Drupal module   which was created by 
  [Joel Stein](https://github.com/joelstein) and 
  [On Fire Media](http://onfiremedia.com/).
