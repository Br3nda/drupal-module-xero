<?php

/**
 * @file xero-contact.tpl.php
 * This is the basic template for a Xero contact.
 * 
 * Available variables:
 * - $contact: the full Contact array for this contact.
 * - $contactid: the internal identifier for this contact.
 * - $company: the (sanitized) company name for this contact.
 * - $contact_name: the (sanitized) contact name, if available, for this contact.
 * - $mail: a formatted mailto link for this contact.
 * - $status: Xero status of this contact ACTIVE or DELETED
 * - $updated: the timestamp when this contact was last updated.
 * - $type: the type of contact, if specified, as either customer or supplier.
 * - $addresses: pre-formatted addresses.
 * - $phones: an array of phone number strings.
 * - $groups: an array of contact group strings
 *
 * @see template_preprocess_xero_contact()
 */

?>
<div class="xero-contact <?php print 'xero-contact-' . $type; ?>">
  <h2 class="title"><?php print $company; ?></h2>
  <?php if (!empty($contact_name)): ?>
  <h3 class="name"><?php print $contact_name; ?></h3>
  <?php endif; ?>

  <div class="meta">
    <span class="updated">Last Updated: <?php print format_date($updated, 'short'); ?></span>
    <span class="status">Status: <?php print $status; ?></span>
  </div>

  <?php if (!empty($mail)): ?>
  <div class="mail"><a href="mailto:<?php print $mail; ?>" title="<?php print t('E-mail Address'); ?>"><?php print $mail; ?></a></div>
  <?php endif; ?>

  <?php if (!empty($addresses)): ?>
  <div class="xero-address-wrapper">
  <?php print theme('xero_addresses', $addresses); ?>
  </div>
  <?php endif; ?>

  <?php if (!empty($phones)): ?>
  <div class="xero-phone-wrapper">
    <?php print theme('item_list', $phones, t('Phone Numbers'), 'ul', array('class' => 'xero-phones')); ?>
  </div>
  <?php endif; ?>

  <?php if (!empty($groups)): ?>
  <div class="xero-group-wrapper">
    <?php print theme('item_list', $groups, NULL, 'ul', array('class' => 'inline xero-contact-group')); ?>
  </div>
  <?php endif; ?>
</div>
